#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b) // pode dizer que espera variáveis diferentes, o que importa é como a função é chamada, no caso swap(x,y)
{                         // tá passado por valor, e não por referência/endereço, dessa forma atual, tá enviando cópia de x e y, não eles de verdade
        int tmp = *a; // int *a endereço de a, outras linhas é deferência de a/b
        *a = *b;
        *b = tmp;
    // correto vai ser *a e *b em todos os casos
}
