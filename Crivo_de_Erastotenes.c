#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NUM 6400

// Função para setar o bit na posição 'pos' no array de bits
void setBit(unsigned int *bitArray, int pos) {
    int index = pos / 32; // Divide por 32 para encontrar o índice do int
    int bitPos = pos % 32; // Encontra a posição do bit dentro do int

    bitArray[index] |= (1 << bitPos); // Seta o bit na posição 'pos'
}

// Função para verificar se o bit na posição 'pos' está setado no array de bits
bool isBitSet(unsigned int *bitArray, int pos) {
    int index = pos / 32; // Divide por 32 para encontrar o índice do int
    int bitPos = pos % 32; // Encontra a posição do bit dentro do int

    return (bitArray[index] & (1 << bitPos)) != 0; // Verifica se o bit está setado
}

// Função para criar um array de bits com os números primos até n
void createBitArray(unsigned int *bitArray, int n) {
    int i, j;
    for (i = 2; i <= n; i++) {
        if (!isBitSet(bitArray, i)) {
            for (j = i + i; j <= n; j += i) {
                setBit(bitArray, j);
            }
        }
    }
}

int main() {
    unsigned int bitArray[(MAX_NUM + 32) / 32] = {0}; // Array para armazenar os bits
    int num;

    createBitArray(bitArray, MAX_NUM);

    printf("Digite um numero (ate %d): ", MAX_NUM);
    scanf("%d", &num);

    if (num >= 2 && num <= MAX_NUM) {
        if (!isBitSet(bitArray, num)) {
            printf("O numero %d eh primo\n", num);
        } else {
            printf("O numero %d nao eh primo\n", num);
        }
    } else {
        printf("Numero fora do intervalo permitido.\n");
    }
        
    return 0;
}
