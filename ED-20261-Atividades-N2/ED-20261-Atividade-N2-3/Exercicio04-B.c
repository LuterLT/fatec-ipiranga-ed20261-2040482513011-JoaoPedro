// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

static int chamadas_rapida;
static int chamadas_ingenua;

// potenciacao rapida O(log exp)
// caso base: exp == 0 -> retorna 1 (qualquer numero elevado a 0 e 1)
// caso recursivo par:  b^n = (b^(n/2))^2  — divide o expoente pela metade
// caso recursivo impar: b^n = b * b^(n-1) — reduz pra caso par
long long potenciaRapida(long long base, int exp) {
    chamadas_rapida++;

    if (exp == 0)
        return 1;   // caso base

    if (exp % 2 == 0) {
        long long metade = potenciaRapida(base, exp / 2);  // caso recursivo par
        return metade * metade;
    } else {
        return base * potenciaRapida(base, exp - 1);  // caso recursivo impar
    }
}

// versao ingenua O(n) — b^n = b * b^(n-1)
long long potenciaIngenua(long long base, int exp) {
    chamadas_ingenua++;
    if (exp == 0) return 1;
    return base * potenciaIngenua(base, exp - 1);
}

int main() {
    long long base;
    int exp;

    struct { long long b; int e; } testes[] = {
        {2, 10}, {3, 7}, {5, 0}, {7, 12}
    };

    printf("%-10s %-8s %-15s %-15s %-12s\n",
           "base^exp", "result", "ch. rapida", "ch. ingenua", "diferenca");

    for (int i = 0; i < 4; i++) {
        base = testes[i].b;
        exp  = testes[i].e;

        chamadas_rapida  = 0;
        chamadas_ingenua = 0;

        long long r1 = potenciaRapida(base, exp);
        long long r2 = potenciaIngenua(base, exp);

        // os dois devem dar o mesmo resultado; diferenca e so no numero de chamadas
        // a versao rapida usa O(log n) chamadas enquanto a ingenua usa O(n)
        printf("%lld^%-6d %-15lld %-15d %-15d %d\n",
               base, exp, r1, chamadas_rapida, chamadas_ingenua,
               chamadas_ingenua - chamadas_rapida);

        (void)r2; // so pra nao dar warning de variavel nao usada
    }

    return 0;
}
