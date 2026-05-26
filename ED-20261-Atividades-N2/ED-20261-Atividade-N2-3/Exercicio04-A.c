// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

// contador de chamadas recursivas (static mantem valor entre chamadas)
static int chamadas;

// caso base 1: inicio > fim — elemento nao esta no vetor, retorna -1
// caso base 2: elemento do meio e igual ao alvo, retorna o indice
// caso recursivo: divide o intervalo pela metade e chama de novo
int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    chamadas++;

    if (inicio > fim)
        return -1;  // caso base: nao encontrado

    int meio = (inicio + fim) / 2;

    if (*(vet + meio) == alvo)
        return meio;  // caso base: encontrado

    if (*(vet + meio) < alvo)
        return buscaBinaria(vet, meio + 1, fim, alvo);  // descarta metade esquerda
    else
        return buscaBinaria(vet, inicio, meio - 1, alvo);  // descarta metade direita
}

int main() {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = 10;

    // busca de elemento presente no meio
    chamadas = 0;
    int idx = buscaBinaria(dados, 0, n - 1, 23);
    printf("Busca por 23: indice = %d | chamadas = %d\n", idx, chamadas);

    // busca de elemento ausente
    chamadas = 0;
    idx = buscaBinaria(dados, 0, n - 1, 99);
    printf("Busca por 99: indice = %d (nao encontrado) | chamadas = %d\n", idx, chamadas);

    // busca do primeiro elemento
    chamadas = 0;
    idx = buscaBinaria(dados, 0, n - 1, 2);
    printf("Busca por  2: indice = %d | chamadas = %d\n", idx, chamadas);

    return 0;
}
