#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

void crivo_de_eratostenes(uint32_t *primo, int n) {
    int fim = (int)sqrt(n);

    // Inicializa todos os bits como 1 (números primos)
    for (int i = 0; i <= n / 32; ++i) {
        primo[i] = 0xFFFFFFFF;
    }

    // Define 0 e 1 como não primos
    primo[0] &= ~3;

    for (int p = 2; p <= fim; ++p) {
        if (primo[p / 32] & (1 << (p % 32))) {
            for (int k = p * p; k <= n; k += p) {
                primo[k / 32] &= ~(1 << (k % 32));
            }
        }
    }
}

int eh_primo(uint32_t *primo, int num) {
    if (num < 2) {
        return 0;
    }

    return (primo[num / 32] & (1 << (num % 32))) != 0;
}

int main() {
    int n = 6400;
    uint32_t primo[200]; // 6400 / 32 = 200
    memset(primo, 0, sizeof(primo)); // Inicializa todos os bytes do array com 0

    crivo_de_eratostenes(primo, n);

    // Exemplos de consulta
    int num;
    printf("Digite um numero para verificar se eh primo (entre 2 e %d): ", n);
    scanf("%d", &num);

    if (eh_primo(primo, num)) {
        printf("%d eh um numero primo.\n", num);
    } else {
        printf("%d nao eh um numero primo.\n", num);
    }

    return 0;
}
