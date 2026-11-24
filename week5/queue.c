const int CAPACITY = 50;

typedef struct
{
    person people[CAPACITY]; // array people do tipo person do tamanho capacity
    int size; // numero de pessoas na queue, vai mudar
} queue; // nome da struct - se é queue geralmente FIFO, OU stack - LIFO

push - botar no topo do stack
pop - remover do topo do stack
