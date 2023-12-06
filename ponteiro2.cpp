#include <stdio.h>

int main() {
    int vetor[5];
    int *ponteiroVetor = &vetor[0];


    printf("Digite 5 valores inteiros:\n");
    for (int i = 0; i < 5; ++i) {
        scanf("%d", &vetor[i]);
    }

    printf("\nO dobro de cada valor:\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", ponteiroVetor[i] * 2);
    }

    return 0;
}