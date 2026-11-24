#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
} candidate;

int main(void)
{
    const int NUM = 3;
    candidate candidates[NUM];
    int highest_vote = 0;

    for (int i = 0; i < NUM; i++)
    {
        candidates[i].name = get_string("Name: ");
        candidates[i].votes = get_int("Votes: ");
    }

    for (int i = 0; i < NUM; i++)
    {
        if (candidates[i].votes > highest_vote)
        highest_vote = candidates[i].votes;
    }

    for (int i = 0; i < NUM; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
