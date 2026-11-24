#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size = get_int("Enter size: ");
    int array[size];
    array[0] = 1;
    for (int i = 1; i <= size; i++)
    {
        array[i] = array[i - 1] * 2;
    }
    for (int i = 0; i < size; i++)
    {
    printf("%i\n", array[i]);
    }

}
