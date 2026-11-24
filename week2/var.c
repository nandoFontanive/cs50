#include <stdio.h>

int plusOne(int);
int timesTwo(int);
int timesTwoChangingGlobal(int);
int global = 0;

int main(void)
{
    printf("Global = %i\n", global);

    printf("Global before +1\n");
    global = 1;
    printf("Global after +1\n");

    printf("Global is: %i\n", global);

    printf("Global before plusOne as overwrite is: %i\n", global);
    global = plusOne(global);
    printf("Global after plusOne as overwrite is: %i\n", global);

    printf("Global before plusOne is: %i\n", global);
    plusOne(global);
    printf("Global after plusOne is: %i\n", global);

    printf("Global before timesTwo func as overwrite is: %i\n", global);
    global = timesTwo(global);
    printf("Global after timesTwo func is: %i\n", global);

    printf("Global before timesTwo is: %i\n", global);
    timesTwo(global);
    printf("Global after timesTwo is: %i\n", global);

    printf("Global before adding +10 is: %i\n", global);
    global = global + 10;
    printf("Global after adding +10 is: %i\n", global);
    printf("Global is: %i\n", global);

    printf("Global before timesTwoChangingGlobal overriding is: %i\n", global);
    global = timesTwoChangingGlobal(global);
    printf("Global after timesTwoChangingGlobal overriding is: %i\n", global);

    printf("Global before timesTwoChangingGlobal is: %i\n", global);
    timesTwoChangingGlobal(global);
    printf("Global after timesTwoChangingGlobal is: %i\n", global);
}

int plusOne(int a)
{
    printf("(inside func) Global before plusOne is: %i\n", global);
    int plusOne = global + 1;
    return plusOne;
}

int timesTwo(int b)
{
    printf("(inside func) Global before timesTwo is: %i\n", global);
    int timesTwo = global * 2;
    return timesTwo;
}

int timesTwoChangingGlobal(int c)
{
    printf("(inside func) Global before timesTwoChangingGlobal is: %i\n", global);
    global = global * 2;
    printf("(inside func) Global after timesTwoChangingGlobal is: %i\n", global);
    return global;
}
