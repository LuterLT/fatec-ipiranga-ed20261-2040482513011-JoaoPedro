// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

int main() {
    int v[] = {10, 20, 30, 40, 50};
    int tam = 5;
    int *ptr;
    int soma = 0;

    // --- a) imprime elementos e enderecos ---
    printf("=== Elementos e enderecos ===\n");
    for (ptr = v; ptr < v + tam; ptr++) {  // ptr++ avanca sizeof(int) bytes
        // * desreferencia ptr, acessando o valor no endereco atual
        printf("Endereco: %p  |  Valor: %d\n", (void *)ptr, *ptr);
    }

    // --- b) soma dos elementos ---
    for (ptr = v; ptr < v + tam; ptr++) {
        soma += *ptr;   // * acessa o inteiro guardado no endereco ptr
    }
    printf("\nSoma total: %d\n", soma);

    // --- c) inversao in-place com dois ponteiros ---
    // inicio aponta pro primeiro elemento, fim pro ultimo
    int *inicio = v;           // inicio = endereco de v[0]
    int *fim    = v + tam - 1; // fim    = endereco de v[4]

    while (inicio < fim) {
        // troca usando soma/subtracao, sem variavel temporaria
        *inicio = *inicio + *fim;   // * escreve no endereco de inicio
        *fim    = *inicio - *fim;   // * le/escreve no endereco de fim
        *inicio = *inicio - *fim;   // * ajusta o valor em inicio

        inicio++;   // avanca ponteiro do comeco
        fim--;      // recua ponteiro do final
    }

    printf("\n=== Vetor invertido ===\n");
    for (ptr = v; ptr < v + tam; ptr++) {
        // * acessa o valor no endereco apontado por ptr
        printf("%d ", *ptr);
    }
    printf("\n");

    return 0;
}
