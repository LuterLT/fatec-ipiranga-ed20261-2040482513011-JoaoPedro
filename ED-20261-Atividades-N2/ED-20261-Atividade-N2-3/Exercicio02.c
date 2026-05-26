// RA: 2040482513011 - Joao Pedro de Franca Assalti

#include <stdio.h>

// calcula e retorna a media aritmetica do vetor
float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *ptr = vet;
    float *fim = vet + n;

    while (ptr < fim) {
        soma += *ptr;   // * acessa o float no endereco apontado por ptr
        ptr++;
    }
    return soma / n;
}

// encontra maior e menor, escrevendo diretamente nos ponteiros recebidos
// nao retorna nada — modifica via referencia os enderecos passados
void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    *maior = *vet;   // * inicializa com o primeiro elemento
    *menor = *vet;

    float *ptr = vet + 1;
    float *fim = vet + n;

    while (ptr < fim) {
        if (*ptr > *maior)   // * compara valor no endereco atual
            *maior = *ptr;   // * escreve no endereco de 'maior'
        if (*ptr < *menor)
            *menor = *ptr;
        ptr++;
    }
}

// divide cada elemento pelo valor maximo, normalizando o vetor
// como recebemos o ponteiro pro array original, alteramos o array diretamente
// se fosse passado por valor (copia) as mudancas nao persistiriam no main
void normalizar(float *vet, int n) {
    float maior, menor_ignorado;
    encontrarExtremos(vet, n, &maior, &menor_ignorado);

    float *ptr = vet;
    float *fim = vet + n;

    while (ptr < fim) {
        *ptr = *ptr / maior;   // * le e escreve no mesmo endereco
        ptr++;
    }
}

void imprimirVetor(float *vet, int n, const char *titulo) {
    printf("\n%s\n", titulo);
    float *ptr = vet;
    float *fim = vet + n;
    int i = 0;

    while (ptr < fim) {
        printf("  [%d] = %.4f\n", i, *ptr);  // * le o valor no endereco
        ptr++;
        i++;
    }
}

int main() {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = 6;
    float media, maior, menor;

    imprimirVetor(notas, n, "Notas originais:");

    calcularMedia(notas, n);
    media = calcularMedia(notas, n);
    encontrarExtremos(notas, n, &maior, &menor);

    printf("\nMedia:  %.4f\n", media);
    printf("Maior:  %.4f\n", maior);
    printf("Menor:  %.4f\n", menor);

    // normalizar recebe o ponteiro pro array real, entao altera o original
    // nao uma copia — por isso as mudancas aparecem no main depois
    normalizar(notas, n);

    imprimirVetor(notas, n, "Notas apos normalizacao:");

    return 0;
}
