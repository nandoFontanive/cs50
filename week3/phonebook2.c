#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    person people[3];

    people[0].name = "John";
    people[0].number = "+1-55-9999";

    people[1].name = "Adam";
    people[1].number = "12345";

    people[2].name = "Yullia";
    people[2].number = "12345";

    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    return 1;
}
