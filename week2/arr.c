#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int array[100];
    for (int i = 0; i < 100; i++)
    {
        array[i] = i;
    }
    printf("%i\n", array[10]);
    printf("%i\n", array[97]);
    printf("%i\n", array[98]);
    printf("%i\n", array[99]);
    printf("%i\n", array[99]);
}
