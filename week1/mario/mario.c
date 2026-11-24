#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_blank(int spaces);
int get_positive_int(void);

int main(void)
{
    int height = get_positive_int();

    for (int i = 0; i < height; i++)
    {
        print_blank((height - 1) - i);
        print_row(i + 1);
    }
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Enter height: ");
    }
    while (n < 1);
    return n;
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

void print_blank(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
}
