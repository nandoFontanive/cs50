#include <cs50.h>
#include <stdio.h>

int calculate_coins(int cents);

int main(void)
{
    int cents = 0;
    int coins = 0;

    // accepts only positive change
    do
    {
        cents = get_int("You want change for how much? ");
    }
    while (cents < 1);
    printf("You asked for change for %i\n", cents);

    // start giving cents
    // creates a variable with the returned value from the func
    coins = calculate_coins(cents);

    printf("Total coins given is: %i\n", coins);
}

int calculate_coins(int cents)
{
    int coins = 0;
    while (cents >= 25)
    {
        coins++;
        cents = cents - 25;
    }

    while (cents >= 10)
    {
        coins++;
        cents = cents - 10;
    }

    while (cents >= 5)
    {
        coins++;
        cents = cents - 5;
    }

    while (cents >= 1)
    {
        coins++;
        cents = cents - 1;
    }
    // return coins only once
    return coins;
}
