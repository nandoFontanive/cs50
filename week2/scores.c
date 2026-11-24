#include <cs50.h>
#include <stdio.h>

const int N = 3;

float average(int lenght, int array[]);

int main(void)
{
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average is %f\n", average(N, scores));
}

float average(int lenght, int array[])
{
    int sum = 0;
    for (int i = 0; i < lenght; i++)
    {
    sum += array[i];
    }
    return sum / (float) lenght;
}


/*#include <stdio.h>

int main(void)
{
    int scores[3];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;

    printf("Average is %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
                                                         // can also cast the int 3 to float 3 using (float) 3, or just use 3.0
}


*/
