#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max (100)
#define min (10)

typedef struct list* list_ptr;
typedef struct list {
    int element;
    list_ptr next;
} list;

void push_stog(list_ptr, int*);
void push_red(list_ptr, int*);
int pop(list_ptr);
int print(list_ptr);
int Rand(void);

int main()
{
    int el;

    srand((unsigned int)time(NULL));

    list stack, queue;
    stack.next = NULL, queue.next = NULL;

    for (int i = 0; i < 10; i++)
    {
        el = Rand();
        push_stog(&stack, &el);
        push_red(&queue, &el);
    }
    printf("Stack:\n");
    print(&stack);
    printf("\nQueue:\n");
    print(&queue);

    printf("\nFirst element popped from stack: %d\nFirst popped from queue: %d\n\n", pop(&stack), pop(&queue));

    return 0;
}
void push_stog(list_ptr stack, int* el)
{
    list_ptr temp = malloc(sizeof(list));
    temp->element = *el;
    temp->next = stack->next;
    stack->next = temp;
}
void push_red(list_ptr ptr, int* el)
{
    while (ptr->next != NULL)
        ptr = ptr->next;

    list_ptr temp = malloc(sizeof(list));
    ptr->next = temp;
    temp->next = NULL;
    temp->element = *el;
}
int pop(list_ptr ptr)
{
    int el;
    if (ptr->next == NULL)
        return -1;
    list_ptr temp = ptr->next;
    el = ptr->next->element;
    ptr->next = ptr->next->next;
    free(temp);

    return el;
}
int Rand(void)
{
    int randBr = 0;
    randBr = (min + (rand() / (RAND_MAX / (max - min + 1) + 1)));
    return randBr;
}
int print(list_ptr ptr)
{
    if (ptr->next == NULL)
        return 0;
    while (ptr->next != NULL) {
        printf("%d\n", ptr->next->element);
        ptr = ptr->next;
    }
    return 0;
}