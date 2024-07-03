#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NUM 6400

// Function to set the bit at position 'pos' in the bit array
void setBit(int *bitArray, int pos) {
    int index = pos / 32; // Divide by 32 to get the index of the int
    int bitPos = pos % 32; // Get the bit position within the int

    bitArray[index] |= (1 << bitPos); // Set the bit at the given position
}

// Function to check if the bit at position 'pos' is set in the bit array
bool isBitSet(int *bitArray, int pos) {
    int index = pos / 32; // Divide by 32 to get the index of the int
    int bitPos = pos % 32; // Get the bit position within the int

    return (bitArray[index] & (1 << bitPos)) != 0; // Check if the bit is set
}

// Function to create the prime number bit array
void createBitArray(int *bitArray, int n) {
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
    int bitArray[(MAX_NUM + 32) / 32] = {0}; // Bit array to store prime numbers
    int num;

    createBitArray(bitArray, MAX_NUM);

    printf("Digite um número: ");
    scanf("%d", &num);

    if (num >= 2 && num <= MAX_NUM && !isBitSet(bitArray, num)) {
        printf("O número %d é primo\n", num);
    } else {
        printf("O número %d não é primo\n", num);
    }

    return 0;
}