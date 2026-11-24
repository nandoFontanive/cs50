#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int a, int b, int c);
int main(void)
{
    int a = get_int("Enter length for a: ");
    int b = get_int("Enter length for b: ");
    int c = get_int("Enter length for c: ");
    valid_triangle(a, b, c);
}

bool valid_triangle(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a)
    {
        return false;
    }
        return true;
}
