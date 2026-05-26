// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

// insere um valor na ABB de forma recursiva
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

// retorna -1 para no nulo (conforme requisito)
// altura do no = maior caminho ate uma folha descendente
int alturaNo(No *no) {
    if (no == NULL) return -1;

    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);

    return 1 + (altEsq > altDir ? altEsq : altDir);
}

// retorna a profundidade do no com 'valor' (distancia ate a raiz)
// retorna -1 se o valor nao existir
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;

    if (valor < raiz->dado)
        return profundidadeNo(raiz->esq, valor, prof + 1);
    else
        return profundidadeNo(raiz->dir, valor, prof + 1);
}

// grau do no = numero de filhos diretos (0, 1 ou 2)
int grauNo(No *no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

// percurso em-ordem pra imprimir grau de cada no
void emOrdemGrau(No *no) {
    if (no == NULL) return;
    emOrdemGrau(no->esq);
    printf("  No %d: grau = %d\n", no->dado, grauNo(no));
    emOrdemGrau(no->dir);
}

void liberarArvore(No *no) {
    if (no == NULL) return;
    liberarArvore(no->esq);
    liberarArvore(no->dir);
    free(no);
}

int main() {
    /*
     * Estrutura da ABB apos inserir: 50 30 70 20 40 60 80 10 25 45 65
     *
     *                  50
     *               /      \
     *             30        70
     *            /  \      /  \
     *          20   40   60   80
     *         /  \    \    \
     *        10  25   45   65
     *
     * Verificacao manual de tres nos:
     *  - No 50 (raiz): altura = 3, profundidade = 0, grau = 2  -> confere com funcoes
     *  - No 30:        altura = 2, profundidade = 1, grau = 2  -> confere
     *  - No 10 (folha):altura = 0, profundidade = 3, grau = 0  -> confere
     */

    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = 11;

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    // --- Parte B-a: alturas ---
    printf("=== Alturas ===\n");
    int nos_altura[] = {50, 30, 70, 20, 10};
    for (int i = 0; i < 5; i++) {
        No *tmp = raiz;
        // percorre manualmente pra achar o no (reuso de profundidadeNo nao serve aqui)
        // solucao simples: funcao auxiliar inline
        No *cur = raiz;
        while (cur && cur->dado != nos_altura[i]) {
            if (nos_altura[i] < cur->dado) cur = cur->esq;
            else cur = cur->dir;
        }
        printf("  alturaNo(%d) = %d\n", nos_altura[i], alturaNo(cur));
        (void)tmp;
    }

    // --- Parte B-b: profundidades ---
    printf("\n=== Profundidades ===\n");
    int nos_prof[] = {50, 30, 70, 45, 10};
    for (int i = 0; i < 5; i++)
        printf("  profundidadeNo(%d) = %d\n", nos_prof[i],
               profundidadeNo(raiz, nos_prof[i], 0));

    // --- Parte B-c: grau em percurso em-ordem ---
    printf("\n=== Grau de cada no (em-ordem) ===\n");
    emOrdemGrau(raiz);

    // --- Parte B-d: altura total da arvore ---
    printf("\n=== Altura total da arvore ===\n");
    printf("  altura = %d\n", alturaNo(raiz));

    liberarArvore(raiz);
    return 0;
}
