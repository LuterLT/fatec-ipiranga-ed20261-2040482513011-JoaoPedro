// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;
    }
    if (valor < raiz->dado)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int alturaNo(No *no) {
    if (no == NULL) return -1;
    int ae = alturaNo(no->esq);
    int ad = alturaNo(no->dir);
    return 1 + (ae > ad ? ae : ad);
}

int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq) g++;
    if (no->dir) g++;
    return g;
}

// imprime ancestrais do pai ate a raiz de forma recursiva
// a recursao desce ate achar o no e imprime na volta (do pai ate a raiz)
void imprimirAncestral(No *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return;

    if (valor < raiz->dado)
        imprimirAncestral(raiz->esq, valor);
    else
        imprimirAncestral(raiz->dir, valor);

    printf("%d ", raiz->dado);
}

// percurso em-ordem na subarvore (funcao auxiliar separada, sem aninhamento)
void percorrerEmOrdem(No *n) {
    if (n == NULL) return;
    percorrerEmOrdem(n->esq);
    printf("%d ", n->dado);
    percorrerEmOrdem(n->dir);
}

// imprime todos os descendentes do no com 'valor' (exceto o proprio no)
void imprimirDescendentes(No *raiz, int valor) {
    No *cur = raiz;
    while (cur && cur->dado != valor) {
        if (valor < cur->dado) cur = cur->esq;
        else cur = cur->dir;
    }
    if (cur == NULL) {
        printf("(no nao encontrado)");
        return;
    }
    // percorre subarvores esq e dir em-ordem, pulando o proprio no
    percorrerEmOrdem(cur->esq);
    percorrerEmOrdem(cur->dir);
}

int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    return 1 + contarDescendentes(no->esq) + contarDescendentes(no->dir);
}

No *buscarNo(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    return buscarNo(raiz->dir, valor);
}

void relatorioNo(No *raiz, int valor) {
    No *no = buscarNo(raiz, valor);
    if (no == NULL) {
        printf("ERRO: no com valor %d nao encontrado na arvore.\n", valor);
        return;
    }

    int prof = profundidadeNo(raiz, valor, 0);
    int alt  = alturaNo(no);
    int grau = grauNo(no);
    int qtdD = contarDescendentes(no->esq) + contarDescendentes(no->dir);

    printf("+----------------------------------+\n");
    printf("| RELATORIO DO NO: %-14d |\n", valor);
    printf("+----------------------------------+\n");
    printf("| Profundidade : %-17d |\n", prof);
    printf("| Altura       : %-17d |\n", alt);
    printf("| Grau         : %-17d |\n", grau);
    printf("| Ancestrais   : ");
    imprimirAncestral(raiz, valor);
    printf("\n");
    printf("| Descendentes : ");
    imprimirDescendentes(raiz, valor);
    printf("\n");
    printf("| Qtd Descend. : %-17d |\n", qtdD);
    printf("+----------------------------------+\n\n");
}

void liberarArvore(No *no) {
    if (no == NULL) return;
    liberarArvore(no->esq);
    liberarArvore(no->dir);
    free(no);
}

int main() {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};

    for (int i = 0; i < 11; i++)
        raiz = inserir(raiz, valores[i]);

    relatorioNo(raiz, 50);
    relatorioNo(raiz, 30);
    relatorioNo(raiz, 10);
    relatorioNo(raiz, 70);

    liberarArvore(raiz);
    return 0;
}
