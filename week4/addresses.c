#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n; //declara o pointer
    printf("%p\n", p); //printa a localização da variável n na memória
    printf("%i\n", *p); //printa o valor da variável (50) - *p aqui significa go there, deferencia o pointer
    // em cs50.h tem o typedef char * string, pra criar o uso do tipo string
    // char *s = "HI!"; s é o endereço de um char
    // comparar strings dá erro pq ele compara 2 endereços, obviamente diferentes, strcmp compara chars individuais, por isso a comparação dá certo
}
