# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

//Computar a raiz quadrada de um argumento A por meio do uso do método
//de Newton-Rapson minimizando as multiplicações. Faça uma função C para resolver esse
//problema e use valores float A entre 50 até 70 com incremento de 1 em 1. Monte uma tabela
//para mostrar os valores A com a respectiva √A que foi calculada e compare esse resultado
//com o valor produzido pela função sqrt da biblioteca math.h do C.

//Para minimizar as multiplicações é necessário começar esse processo com valor inicial x0 mais
//próximo de √A quanto possível.
//Use a estrutura da IEEE-754 para eliminar a multiplicação por 1/2 na equação de recorrência de Newton-
//Rapson, bem como para estimar um bom valor para x0.
#define pi 3.14159265358979323846
const float sqrt2 = 1.4142135623730950488016887;
const float invsqrt2 = 1/sqrt2;
const int B = 127;

typedef union floatIEEE{
    float x; // valor decimal
    struct {
    // a ordem de definição dos campos é importante}
    unsigned int f : 23; // 23 bits para a fração damantissa (0.xxx...)
    unsigned int E : 8; // 8 bits para o expoenteenviezado por B = 127
    unsigned char s : 1; // 1 bit para o sinal damantissa
    }bits;
}floatIEEE;

void computeSquareRoot() {
    float A = 9.0;
    floatIEEE x1;
    floatIEEE x0 = {A};

    int e = ((x0.bits.E) - B);
    x0.bits.f >>= 1; // (f = f/2)
    if (e & 1) { // e = x0.bits.E
    x0.bits.E = ((e+1) >> 1) + B;
    x0.x *= invsqrt2;
    }
    else{
    x0.bits.E = ((e) >> 1) + B;
    }

    x1.x = x0.x;
    do { // newton-rapson
    x0.x = x1.x; // estimativa atual
    // resolver xk + A/xk

    x1.x = (x0.x + A/x0.x); // próxima estimativa
    // resolver a multiplicação por 1/2
    x1.bits.E--; // x1.bits.E = x1.bits.E – 1;
    } while (x0.x > x1.x);

    printf("The square root of %f is %f\n", A, x0.x);
}

int main() {
    computeSquareRoot();
    return 0;
}
