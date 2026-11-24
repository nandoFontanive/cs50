#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // changes s[i] to uppercase
            // can also use 32 instead of ('a' - 'A')
            printf("%c", s[i] - ('a' - 'A'));
            // using library:
            // printf("%c", toUpper(s[i])); can just delete de else {...} if using library
        }
        else
        {
            // just print s[i]
            printf("%c", s[i]);
        }

    }
    printf("\n");
}

