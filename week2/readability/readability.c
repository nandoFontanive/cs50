#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float check_grade(float number_letters, float number_words, float number_sentences);
float count_letters(string text);
float count_spaces(string text);
float count_sentences(string text);
void validate_text(string text);

int main(void)
{
    // Receives text from user
    string text = get_string("Text: ");

    // Checks if text is valid
    validate_text(text);

    // Calls function to count number of spaces, sentences, words and letters
    float number_spaces = count_spaces(text);
    float number_sentences = count_sentences(text);
    float number_words = number_spaces + 1;
    float number_letters = count_letters(text);

    // Calculates the reading grade
    float grade = check_grade(number_letters, number_words, number_sentences);

    if (grade < 2)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
}

// Defines function to calculate grade
// index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text: that is, the number of letters
// divided by the number of words, all multiplied by 100. S is the average number of sentences per
// 100 words in the text: that is, the number of sentences divided by the number of words, all
// multiplied by 100.
float check_grade(float number_letters, float number_words, float number_sentences)
{
    float average_letters = (number_letters / number_words);
    float average_sentences = (number_sentences / number_words);
    float index = ((0.0588 * average_letters * 100) - (0.296 * average_sentences * 100) - 15.8);

    return round(index);
}

// Defines function to count number of letters
float count_letters(string text)
{
    float number_letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            number_letters++;
        }
    }
    return number_letters;
}

// Defines function to count number of spaces
float count_spaces(string text)
{
    float number_spaces = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            number_spaces++;
        }
    }
    return number_spaces;
}

// Defines function to count number of sentences
float count_sentences(string text)
{
    float number_sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            number_sentences++;
        }
    }
    return number_sentences;
}

// Defines function to check if text is valid
void validate_text(string text)
{
    if (text[0] == ' ' || text[0] == '.' || text[0] == '!' || text[0] == '?')
    {
        printf("Please enter a valid text\n");
        text = get_string("Text: ");
    }
}
