#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // checks if received an argument or not
    if (argc != 2)
        {
            printf("Enter a word.\n");
            return 1;
            // exits program
        }

    // receives inserted text directly from command line as an argument
    string text = argv[1];

    // checks if every character is a letter
    for (int i = 0, length = strlen(text); i < length; i++)
    // better way to write the for loop
        {
            if (!isalpha(text[i]))
                {
                    printf("Not a letter\n");
                    return 2;
                }
        }

    // check if entered text is alphabetical
    for (int i = 1; i < strlen(text); i++)
    // worse way to write the for loop, as it checks the string lenght every loop
    {
        if (text[i] < text[i - 1])
        {
        printf("False\n");
        // if not alphabetical, stop
        return 0;
        }
    }
    // if program did not stop, print true, since it is alphabetical
    printf("True\n");
}
