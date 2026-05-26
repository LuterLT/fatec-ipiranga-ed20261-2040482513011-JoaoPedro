// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

// troca os valores sem variavel temporaria, so usando soma e subtracao
// recebe os enderecos das duas variaveis
void trocar(int *a, int *b) {
    // *a passa a ter a soma dos dois valores
    *a = *a + *b;   // * desreferencia: acessa o valor no endereco apontado por 'a'
    // *b recebe a diferenca, ou seja, o valor original de *a
    *b = *a - *b;   // * desreferencia 'b' e escreve o antigo valor de 'a' nele
    // *a agora recebe o valor original de *b
    *a = *a - *b;   // * desreferencia 'a' e escreve o antigo valor de 'b'
}

int main() {
    int x = 15;
    int y = 42;

    // & retorna o endereco de memoria de x e y
    printf("Enderecos: x = %p  |  y = %p\n", (void *)&x, (void *)&y);
    printf("Antes da troca:  x = %d, y = %d\n", x, y);

    // passa os enderecos (&) para a funcao poder alterar os originais
    trocar(&x, &y);  // & passa o endereco de x e y

    printf("Depois da troca: x = %d, y = %d\n", x, y);

    return 0;
}
