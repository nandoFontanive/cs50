#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_argument_received(int argument_count, string argv[]);
void convert_plaintext_to_ciphertext(string plain_text, int k);
int convert_string_int(string argv[]);

int ALPHABET_SIZE = 26;

// char LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
//                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
// char UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
//                 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, string argv[])
{
    int argument_count = argc;

    // Checks number of arguments and if they are positive
    if (check_argument_received(argument_count, argv) != 0)
    {
        return 1;
    }

    int number_rotations = convert_string_int(argv);

    // If argument is fine, requires plaintext
    string plain_text = get_string("plaintext:  ");

    convert_plaintext_to_ciphertext(plain_text, number_rotations);
}

// Convert plain_text to cipher_text
void convert_plaintext_to_ciphertext(string plain_text, int number_rotations)
{
    int len = strlen(plain_text);
    char rotated_string[len + 1]; // +1 for the null terminator
    for (int i = 0; i < len; i++)
    {
        if (isalpha(plain_text[i]))
        {
            if (islower(plain_text[i]))
            {
                int rotated_char = (plain_text[i] - 'a' + number_rotations) % 26;
                rotated_string[i] = rotated_char + 'a';
            }
            else
            {
                int rotated_char = (plain_text[i] - 'A' + number_rotations) % 26;
                rotated_string[i] = rotated_char + 'A';
            }
        }
        else
        {
            rotated_string[i] = plain_text[i];
        }
    }
    rotated_string[len] = '\0';
    printf("ciphertext: %s\n", rotated_string);
}

// Same as function atoi, inside stdlib.h
int convert_string_int(string argv[])
{
    int final_n = 0;
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        int initial_n = (argv[1][i]) - '0';
        final_n = final_n * 10 + initial_n;
    }
    return final_n;
}

int check_argument_received(int argument_count, string argv[])
{
    if (argument_count != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
        if (!isdigit(argv[1][i]) || argv[1][i] == '-')
        {
            printf("Usage: ./caesar key\n");
            return 2;
        }
    return 0;
}
