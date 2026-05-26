// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

int contadorMovimentos = 0;

// funcao recursiva com rastreamento de profundidade
// n     = quantidade de discos
// nivel = profundidade atual da recursao (pra identar a saida)
void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {

    // caso base: so um disco, move direto
    if (n == 1) {
        // identa proporcional ao nivel atual
        for (int i = 0; i < nivel * 2; i++) printf(" ");
        printf("[nivel %d] Mover disco 1 de %c para %c\n", nivel, origem, destino);
        contadorMovimentos++;
        return;
    }

    // caso recursivo:
    // 1. leva os n-1 discos de cima pro auxiliar, usando destino como apoio
    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);

    // 2. move o disco maior (disco n) pro destino
    for (int i = 0; i < nivel * 2; i++) printf(" ");
    printf("[nivel %d] Mover disco %d de %c para %c\n", nivel, n, origem, destino);
    contadorMovimentos++;

    // 3. leva os n-1 discos do auxiliar pro destino, usando origem como apoio
    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main() {
    int testes[] = {1, 3, 4};
    int qtd = 3;

    for (int t = 0; t < qtd; t++) {
        int n = testes[t];
        contadorMovimentos = 0;

        printf("\n========== Hanoi com n = %d ==========\n", n);
        hanoi(n, 'A', 'C', 'B', 0);
        printf("Total de movimentos: %d\n", contadorMovimentos);
    }

    return 0;
}
