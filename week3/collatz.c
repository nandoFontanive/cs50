#include <cs50.h>
#include <stdio.h>

int collatz(int n, int counter);

int main(void)
{
    int n = get_int("Insert n: ");
    int counter = 0;
    collatz(n, counter);
}

int collatz(int n, int counter)
{

    if (n == 1)
    {
        printf("Counter = %i\n", counter);
        return 1;
    }

    else
    {
        if (n % 2 == 0)
        {
            counter++;
            n = (n / 2);
            printf("%i -> ", n);
            return collatz((n), counter);
        }
        else
        {
            counter++;
            n = (3 * n + 1);
            printf("%i -> ", n);
            return collatz((n), counter);
        }
    }
    printf("Counter = %i\n", counter);
    return counter;
}

/*
Doug:
int collatz(int n)
{
    // base case
    if (n == 1)
        return 0;

        // even numbers
    else if ((n % 2) == 0)
        return 1 + collatz(n/2);

        // odd numbers
    else
        return 1 + collatz(3*n + 1);
}
*/
