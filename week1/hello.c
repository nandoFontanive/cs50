#include <cs50.h>
#include <stdio.h>


int main(void)
{
    string answer = get_string("What's your name? ");
    int typedResult = get_int("Digite aqui ");
    printf("hello, %s\n", answer);
    printf("digitado, %i\n", typedResult);
}
