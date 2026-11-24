(doug)
structures - super variavel com vários tipos misturados
coletam em uma caixa/container diferentes dados de diferentes tipos
separa elas em um arquivo .h

struct car
{
    int year;
    char mode[10];
    char plate[7];
    int odometer;
    double engine_size;
};

declara variavel
struct car mycar;

acessa via car.plate , por ex:
mycar.year = 2011;
strcpy(mycar.plate, "CS50"); // copia a string pra variável
mycar.odometer = 50505;

pra alocar structs dinamicamente, sem definir o tamanho antes
dereference o pointer pra estrutura, pra depois acessar seus campos
struct car *mycar = malloc(sizeof(struct car));

acessar:

(*mycar).year = 2011;
mycar->year = 2011;

strcpy((*mycar).plate, "CS50");
strcpy((mycar->plate, "CS50");

(*mycar).odometer = 50505;
mycar->odometer = 50505;

dereferencia o pointer na esquerda acessa o campo na direita:

=========
singly linked lists
structs n conectam elementos
difícil e caro/lento adicionar dados no meio de arrays, difícil trocar seu tamanho depois de declarado

dá pra combinar o que já foi aprendido pra uma singly linked list pra aumentar e diminuir lista de boa
é um struct especial com algum dado de algum tipo (int, char) e um pointer para outro nodo do mesmo tipo
assim formando uma cadeia de elementos linkados do início até o fim

typedef struct sllist //nome temporário, já que sllnode só existirá na última linha
{
    VALUE val;
    struct sllist* next;
}
sllnode; //nome desejado, criado aqui

criar uma
sllnode* create (VALUE val);
retorna um pointer

search
bool find(sllnode* head, VALUE val);
sempre keep track do 1o elemento da lista, talvez até em variável global
usa um pointer traversal, duplicata do original apontando pra cabeça da lista

n consegue usar list[2], n tem motivo pra manter algum tipo de ordem

inserir
sllnode* insert(sllnode* head, VALUE val); // pointer pro 1o elemento é o jeito que se refere a toda lista
retorna a nova head da lista
novo valor é populado no início da lista, pq isso pode ser feito imediatamente
muito importante primeiro apontar o pointer pra cabeça velha da lista e depois apontar a cabeça da lista pra posição nova, recém criada
ou seja conecta o novo elemento na lista, deixar tudo chained junto, pra depois ajustar o pointer da head antiga pra head nova
tudo isso pra evitar deixar a lista antiga orfanada

deletar
void destroy(sllnode* head);
avalia cada pedaço da lista até achar um null, aí deleta o resto da lista e libera o nodo (funciona via recursão)
se não acha null, segue o ponteiro até achar um, iterando toda a lista, até eventualmente achar o null

=======

doubly-linked lists
usar somente se precisa deletar um node específico no meio da lista, pq vai precisar mais memória
possibilita se movimentar nas duas direções da lista linkada
adiciona um pointer extra na definição da struct:
typedef struct dllist
{
    VALUE val;
    struct dllist* prev;
    struct dllist* next;
}
dllnode;

inserir novo nodo

dllnode* insert(dllnode* head, VALUE val);
ao criar novo nodo, preenche data dele, coloca pointer next, adiciona pointer previous na antiga cabeça da lista, determina quem é o novo começo da lista

deletar
void delete(dllnode* target);
nos cantos da lista é um pouco diferente
skip o nodo do meio que vai ser deletado, ajustando os pointers next e previous
dropa o nodo a ser deletado, sem quebrar a cadeia

==========

stacks
implementada como array ou linked list
dados adicionados via LIFO, so pode fazer push e pop

typedef struct_stack

{
VALUE array[CAPACITY];
int top; // qual o 'ultimo dado adicionado ao stack

}
stack;

pode criar usando
stack s;

void push(stack* s, VALUE data)
funcao push aceita um pointer pro stack - pra mandar um valor mesmo, pra mudar o stack mesmo, e nao uma copia dele

value pop(stack*s)
pop remove, contrário do pop, basicamente, retorna o valor apagado (pra nao só perder ele)

int x = pop(&s)

stacks via linked lists
typedef struct_stack
{
VALUE val;
struct _stack *next
}
stack;

bem parecida com single linked lis
continuar mantendo pointer pra head
=========
queues
parecido com stack, com diferença de ser FIFO ao invés de LIFO
enqueue - push, adiciona novo elemento ao fim da fila
dequeue - pop, retira elemento mais velho do início da fila

typedef struct _queue
{
    VALUE array[capacity];
    int front; // frente da fila, n muda quando um elemento é adicionado, exatamente pra saber onde começou
    int size; // n precisa monitorar a posição do último membro
}
queue;

implementa com
queue q;

void enqueue(queue* q, VALUE data);
enqueue(&q, 28);

front + size = indica onde vai o próximo elemento

int x = dequeue(&q); //oq sai da fila vai pro x

implementando como doubly-linked list
typedef struct _queue
{
    VALUE val;
    struct _queue *prev;
    struct _queue *next;
}
queue;

manter ponteiros pro início e fim da fila, idealmente via variável global
enqueue(tail, 10)
dequeue(head)
==========
hash tables

combina random access do array com dinamismo linked list
ordenar e sort é bem ruim
só é bom de usar se n é importante sort os dados
combina hash function e array
roda a função hash com dados, ele devolve um número que vai pro array

int x = hash("John")
// x é 4
hashtable[x] = "John"

unsigned int hash(char* str)
{
    int sum = 0;
    for (int j = 0; str[j] != '\0; j++) // outra forma de usar o strlength, qdo chega no \0 é pq chegou no fim da string
        {
            sum += str[j];
        }
    return sum % HASH_MAX;
}

pra ver se John tá na hash table, roda o hash de novo, se encontrar, está na hash table
se cai na mesma posição, há colisão, vai pro próximo (linear probing), oq pode ser problema se ocorrer mtas vezes fica lento (clustering)
solução pra isso: chaining, podendo usar linked chains ao invés de arrays
==========
tries usa V ou F, seguindo um roadmap, sem colisões, se n encontra, dado n existe
sai do tronco e vai seguindo os nodos (folhas) através de ponteiros, em caso de datas, 10 opções a cada nodo (código abaixo)

key:value
array é o índice, value é o dado
hash table key é o hash code, value é uma linked list de dados hasheando pra aquele hash code
em tries,

typedef struct _trie
{
    char university[20]
    struct _trie* paths[10]
}
trie;

busca indo passo em passo, se n encontra, n existe o dado buscado

melhor de todas, mas ocupa bastante espaço

==========
data structures
em resumo são 4 tipos, escolhe dependendo do uso
arrays, linked lists, hash tables, tries

==========
(yulia)
pointers guardam endereços

