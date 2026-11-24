#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");

    //char *t = s; faz t igual a s, então ao mudar um, muda o outro tb
    char *t = malloc(strlen(s) + 1); //aloca memória, em t tem o endereço do chunk da memória, do 1o byte da memória

    if (t == NULL) // bogus return
    {
        return 1;
    }

    strcpy(t, s); //destination, source; substitui o abaixo:
    // for (int i = 0, n = strlen(s); i <= n; i++) // uso de <= faz com que o null char tb seja iterado
    // {
    //     t[i] = s[i]; //copia todos chars de s pra t
    // }
    // rodar gargaba | less pra exibir 1 tela por vez

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
}
