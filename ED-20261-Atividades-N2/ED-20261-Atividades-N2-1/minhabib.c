/* ============================================================================
 * Fatec Ipiranga - Disciplina: Estrutura de Dados - Prof. Verissimo
 * Atividade N2-1: Explorando Arvore Binaria
 * Aluno: João Pedro de França Assalti
 * RA: 2040482513011
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minhabib.h"

// Busca(interna) ///////////////////////////////////////////////////////////

static No* busca(No *r, int val) {
    if (r == NULL || r->valor == val) return r;
    if (val < r->valor) return busca(r->esq, val);
    return busca(r->dir, val);
}

// Nos Internos //////////////////////////////////////////////////////////////

static void pegaInternos(No *r, int *v, int *t) {
    if (r == NULL) return;
    if (r->esq != NULL || r->dir != NULL)
        v[(*t)++] = r->valor;
    pegaInternos(r->esq, v, t);
    pegaInternos(r->dir, v, t);
}

void imprimir_nos_internos(No *r) {
    int v[100], t = 0;
    pegaInternos(r, v, &t);
    printf("Nos Internos:\n");
    for (int i = 0; i < t; i++) {
        printf("%d", v[i]);
        if (i < t - 1) printf(", ");
    }
    printf("\n\n");
}

// Folhas ////////////////////////////////////////////////////////////////////

static void pegaFolhas(No *r, int *v, int *t) {
    if (r == NULL) return;
    if (r->esq == NULL && r->dir == NULL)
        v[(*t)++] = r->valor;
    pegaFolhas(r->esq, v, t);
    pegaFolhas(r->dir, v, t);
}

void imprimir_folhas(No *r) {
    int v[100], t = 0;
    pegaFolhas(r, v, &t);
    printf("Nos Externos (Folhas):\n");
    for (int i = 0; i < t; i++) {
        printf("%d", v[i]);
        if (i < t - 1) printf(", ");
    }
    printf("\n\n");
}

// Niveis ////////////////////////////////////////////////////////////////////

void imprimir_niveis(No *r, int nivel_atual) {
    if (r == NULL) return;
    printf("Nivel %d: %d\n", nivel_atual, r->valor);
    imprimir_niveis(r->esq, nivel_atual + 1);
    imprimir_niveis(r->dir, nivel_atual + 1);
}

// Altura ////////////////////////////////////////////////////////////////////

int calcular_altura(No *n) {
    if (n == NULL) return -1;
    int esq = calcular_altura(n->esq);
    int dir = calcular_altura(n->dir);
    return 1 + (esq > dir ? esq : dir);
}

// Profundidade //////////////////////////////////////////////////////////////

int calcular_profundidade(No *r, int val, int profundidade_atual) {
    if (r == NULL) return -1;
    if (r->valor == val) return profundidade_atual;
    int e = calcular_profundidade(r->esq, val, profundidade_atual + 1);
    if (e != -1) return e;
    return calcular_profundidade(r->dir, val, profundidade_atual + 1);
}

// Ancestrais////////////////////////////////////////////////////////////////

static int pegaAncestrais(No *r, int val, int *v, int *t) {
    if (r == NULL) return 0;
    if (r->valor == val) return 1;
    if (pegaAncestrais(r->esq, val, v, t) ||
        pegaAncestrais(r->dir, val, v, t)) {
        v[(*t)++] = r->valor;
        return 1;
    }
    return 0;
}

void imprimir_ancestrais(No *r, int val) {
    int v[100], t = 0;
    pegaAncestrais(r, val, v, &t);
    printf("Ancestrais: ");
    if (t == 0) {
        printf("(nenhum - eh a raiz)");
    } else {
        for (int i = 0; i < t; i++) {
            printf("%d", v[i]);
            if (i < t - 1) printf(", ");
        }
    }
    printf("\n");
}

// Descendentes//////////////////////////////////////////////////////////////

static void pegaDesc(No *n, int *v, int *t) {
    if (n == NULL) return;
    v[(*t)++] = n->valor;
    pegaDesc(n->esq, v, t);
    pegaDesc(n->dir, v, t);
}

void imprimir_descendentes(No *n) {
    int v[100], t = 0;
    pegaDesc(n->esq, v, &t);
    pegaDesc(n->dir, v, &t);
    printf("Descendentes: ");
    if (t == 0) {
        printf("(nenhum - eh folha)");
    } else {
        for (int i = 0; i < t; i++) {
            printf("%d", v[i]);
            if (i < t - 1) printf(", ");
        }
    }
    printf("\n");
}

// SubArvore(interna) //////////////////////////////////////////////////////

static void desenhaArvore(No *r, const char *pref, int ultimo, int ehRaiz) {
    if (r == NULL) return;

    if (ehRaiz) {
        printf("%d\n", r->valor);
    } else {
        printf("%s%s%d\n", pref, ultimo ? "`-- " : "|-- ", r->valor);
    }

    char novoPref[512];
    if (ehRaiz)
        snprintf(novoPref, sizeof(novoPref), "%s", "");
    else
        snprintf(novoPref, sizeof(novoPref), "%s%s",
                 pref, ultimo ? "    " : "|   ");

    int temEsq = (r->esq != NULL);
    int temDir = (r->dir != NULL);

    if (temEsq) desenhaArvore(r->esq, novoPref, !temDir, 0);
    if (temDir) desenhaArvore(r->dir, novoPref, 1, 0);
}

// Funcao central ////////////////////////////////////////////////////////////

void analisar_arvore(No *raiz, int valorBusca) {
    printf("Raiz:\n%d\n\n", raiz->valor);
    imprimir_nos_internos(raiz);
    imprimir_folhas(raiz);
    printf("Niveis:\n");
    imprimir_niveis(raiz, 0);
    printf("\n");

    No *no = busca(raiz, valorBusca);
    if (no == NULL) {
        printf("No %d nao encontrado.\n", valorBusca);
        return;
    }

    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;

    printf("Diagnostico do no %d:\n", valorBusca);
    printf("Grau: %d\n", g);
    imprimir_ancestrais(raiz, valorBusca);
    imprimir_descendentes(no);
    printf("Altura: %d\n", calcular_altura(no));
    printf("Profundidade: %d\n\n", calcular_profundidade(raiz, valorBusca, 0));

    printf("Subarvore (raiz %d):\n", valorBusca);
    desenhaArvore(no, "", 1, 1);
    printf("\n");
}