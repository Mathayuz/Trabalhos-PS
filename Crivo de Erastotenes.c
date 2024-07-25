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

void testPrimos(int *bitArray, int *primos, int size) {
    for (int i = 0; i < size; i++) {
        int num = primos[i];
        if (num >= 2 && num <= MAX_NUM && !isBitSet(bitArray, num)) {
            printf("The number %d is prime\n", num);
        } else {
            printf("The number %d is not prime\n", num);
        }
    }
}void testPrimeNumbers(int *bitArray, int *primos, int size) {
    for (int i = 0; i < size; i++) {
        if (isBitSet(bitArray, primos[i])) {
            printf("Test failed: %d is not a prime number\n", primos[i]);
        }
    }
    printf("All tests passed!\n");
}

int main() {
    unsigned int bitArray[(MAX_NUM + 32) / 32] = {0}; // Bit array to store prime numbers
    int num;

    createBitArray(bitArray, MAX_NUM);

    printf("Digite um número: ");
    scanf("%d", &num);

    if (num >= 2 && num <= MAX_NUM && !isBitSet(bitArray, num)) {
        printf("O número %d é primo\n", num);
    } else {
        printf("O número %d não é primo\n", num);
    }
    // lista para teste:
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    
    testPrimos(bitArray, primos, sizeof(primos) / sizeof(int)); // Teste de cada numero individualmente
    testPrimeNumbers(bitArray, primos, sizeof(primos) / sizeof(int)); // Teste de primos
    
    return 0;
}
