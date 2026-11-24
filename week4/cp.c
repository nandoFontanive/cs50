#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main (int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb"); //rb read em binário
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;
    while(fread(&b, sizeof(b), 1, src) !=0) //endereço de b, tamanho de b, le 1 byte por vez, a partir do source, enquanto n der erro -> enfim, itera todos bytes, 1 por 1
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}

