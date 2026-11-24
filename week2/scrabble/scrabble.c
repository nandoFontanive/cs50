#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int N = 26;
const char POINTS_ARRAY[N] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                              1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void print_winner(int player1_score, int player2_score);
void convert_to_lowercase(string word);

int main(void)
{
    // Receives strings and checks if is a word
    string player1_word = get_string("Player 1 word: ");
    string player2_word = get_string("Player 2 word: ");

    // Convert words to lowercase
    convert_to_lowercase(player1_word);
    convert_to_lowercase(player2_word);

    // Compute score
    int player1_score = compute_score(player1_word);
    int player2_score = compute_score(player2_word);

    // Checks winner
    print_winner(player1_score, player2_score);
}

int compute_score(string word)
{
    int score = 0;

    // Scores table

    // Computes the score: word[i] - 'a' converts character to index
    // subtracting 'a' gives the position of the character in the alphabet ('a' becomes 0, 'b'
    // becomes 1) index is used to access the corresponding score in POINTS_ARRAY
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        score = score + POINTS_ARRAY[word[i] - 'a'];
    }
    return score;
}

void print_winner(int player1_score, int player2_score)
{
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

void convert_to_lowercase(string word)
{
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        word[i] = tolower(word[i]);
    }
}
