#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // int list[3];

    // list[0] = 1;
    // list[1] = 2;
    // list[2] = 3;

    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%i\n", list[i]);
    int *list = malloc(3 * sizeof(int));

    if (list == NULL)
    {
        free(list) // libera list do 1o malloc
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Time passes, realocando pra array maior:

    // int *tmp = malloc(4 * sizeof(int));
    int *tmp = realloc(list, 4 * sizeof(int)); // cria novo array só um pouco maior
    if (tmp == NULL)
    {
        return 1;
    }

    // for (int i = 0; i < 3 ; i++) n  precisa disso com realloc
    // {
    //     tmp[i] = list[i];
    // }

    tmp[3] = 4;
    free(list);

    list = tmp; //renomeia array grande de 4 pra list

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // time passes
    free(list); // libera lista maior
    return 0;
}

// linked list

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL; // quadradinho amarelo mais à esquerda

    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node))
        if (n == NULL)
        {
            return 1;
        }
        (*n).number = get_int("Number: "); //vai pro chunk de memória criado, number dentro dele
        n->number = 1; // sintaxe melhor

        (*n).next = NULL;
        n->next = NULL; // sintaxe melhor

        list = n; // associa list com o quadrado n e sua seta, criando 2 setas, podendo só apagar n depois disso
        //mas isso pode dar problemas em loops
        n-> next = list;
        list = n; // agora pode apagar o n->next = NULL



        // pra append no final da lista: cria ela, vai seguindo até chegar no null, aí sim appenda
        // se a lista n existe no início
        // if list is empty
        if (list == NULL)
        {
            list = n; // novamente, faz com que o pointer list tenha o mesmo pointer de n, n importa qual/oq é a variável em si
        }
        // if list has numbers already
        else
        {
            for (node* ptr = list; ptr != NULL; ptr = ptr->next) // int i, i < x, i++ ---- outra forma de usar for, provavelmente será usado nos exercícios...
            {
                // if at end of list
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // time passes

    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next; //vai seguindo a seta
    }

    // OU

    for (node *ptr = list; ptr != NULL; ptr = ptr-> next)
    {
        printf("%i\n", ptr->number);
    }

// time passes

node *ptr = list;
while (ptr != NULL)
{
    node *next = ptr->next;
    free(ptr); //n pode mais mexer mais nesse endereço liberado, usa a linha acima pra evitar isso
    ptr = next;
}


    return 0;
}

// para árvore binária
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;
