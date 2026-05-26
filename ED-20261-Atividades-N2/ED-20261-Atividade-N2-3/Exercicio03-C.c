// RA: 2040482513011 - Joao Pedro de Franca Assalti

// Parte C - versao com o parametro nivel explicitado e indentacao proporcional
// (a logica de nivel ja estava na Parte A, aqui fica isolado pra facilitar leitura)

#include <stdio.h>

int contadorMovimentos = 0;

void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {

    // caso base
    if (n == 1) {
        for (int i = 0; i < nivel * 2; i++) printf(" ");
        printf("[prof. %d] disco 1: %c --> %c\n", nivel, origem, destino);
        contadorMovimentos++;
        return;
    }

    // move n-1 discos pro auxiliar primeiro
    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);

    // move o maior disco pro destino
    for (int i = 0; i < nivel * 2; i++) printf(" ");
    printf("[prof. %d] disco %d: %c --> %c\n", nivel, n, origem, destino);
    contadorMovimentos++;

    // move os n-1 discos do auxiliar pro destino
    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main() {
    int valores[] = {1, 3, 4};

    for (int i = 0; i < 3; i++) {
        int n = valores[i];
        contadorMovimentos = 0;
        printf("\n--- Hanoi n=%d (indentacao mostra profundidade da recursao) ---\n", n);
        hanoi(n, 'A', 'C', 'B', 0);
        printf("Movimentos totais: %d\n", contadorMovimentos);
    }

    return 0;
}
