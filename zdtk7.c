#include <stdio.h>
#include <stdlib.h>

typedef struct lista* lista_pok;
typedef struct lista {
    int broj;
    char operacija;
    lista_pok next;
} lista;

void pop_stog(lista_pok);
void pop_to_postfix(lista_pok, lista_pok, int);
void postfix(lista_pok, lista_pok, int);
void pop(lista_pok, int);
void push_int(lista_pok, int, int*);
void push_char(lista_pok, int);
void push_end(lista_pok, lista_pok);
void reverse_print(lista_pok);
void zagrade(lista_pok, lista_pok);
int izracun(lista_pok, lista_pok);
int racun(char, int, int);
int is_operator(int);
int is_number(int);
int print(lista_pok);

int main(void)
{
    int c, a = 0, b = 0, * d;
    lista stack, stack2, post;
    stack.next = NULL, stack2.next = NULL, post.next = NULL;

    FILE* pok = fopen("datoteke/infiks.txt", "r+");

    while (!(feof(pok))) {
        c = fgetc(pok);
        if (is_number(c)) {
            push_int(&post, c - 48, &a); 
            a = 1;
        }
        else if (is_operator(c)) {
            a = 0;
            push_char(&stack, c); 
            postfix(&post, &stack, c); 
        }
        else
            a = 0;
    }

    push_end(&post, &stack);
    printf("Postfix izraz: ");
    reverse_print(post.next); 
    printf("\n");

    printf("Rezultat: %d\n", izracun(post.next, &stack2)); 

    fclose(pok);
    return 0;
}
void pop_stog(lista_pok pok)
{
    lista_pok temp = pok->next;
    pok->next = pok->next->next;
    free(temp);
}
int izracun(lista_pok post, lista_pok stog)
{
    int broj = 0;
    lista_pok temp, stog_pok, pok = post;
    if (pok == NULL)
        return broj;
    izracun(pok->next, stog);
    if (pok->operacija == '\0') {
        temp = malloc(sizeof(lista));
        temp->broj = pok->broj;
        temp->operacija = '\0';
        temp->next = stog->next;
        stog->next = temp;
    }
    else {
        if (stog->next != NULL) {
            stog_pok = stog->next;
            if (stog_pok->next != NULL) {
                broj = racun(pok->operacija, stog->next->broj, stog->next->next-broj);
                stog->next->next->broj = broj;
                pop_stog(stog);
            }
            else
                return broj;
        }
        else
            return broj;
    }
    return broj;
}
void reverse_print(lista_pok pok)
{
    if (pok == NULL)
        return;
    reverse_print(pok->next);
    if (pok->operacija != '\0')
        printf("%c  ", pok->operacija);
    else
        printf("%d ", pok->broj);
}
int racun(char c, int y, int x)
{
    switch (c) {
    case '*':
        return(x * y);
        break;
    case '/':
        return(x / y);
        break;
    case '+':
        return(x + y);
        break;
    case '-':
        return(x - y);
        break;
    default:
        return -1;
    }
}
void postfix(lista_pok post, lista_pok stack, int x)
{
    lista_pok temp = stack->next;
    if (temp->next == NULL)
        return;
    int broj = temp->broj;
    if (broj == 3) {
        zagrade(stack, post);
        return;
    }
    else if (broj == 2)
        return;

    while (temp->next != NULL) {
        if (broj <= temp->next->broj && temp->next->broj < 2)
            pop_to_postfix(post, stack, temp->next->operacija);
        else
            return;
        temp = temp->next;
    }
}
void zagrade(lista_pok stack, lista_pok post)
{
    lista_pok temp, stack_free;
    lista_pok head_free = stack->next;
    stack->next = stack->next->next;
    free(head_free);
    while (stack->next->broj != 2) {
        temp = (lista_pok)malloc(sizeof(lista));
        temp->next = post->next;
        post->next = temp;
        temp->operacija = stack->next->operacija;
        temp->broj = 0;

        stack_free = stack->next;
        stack->next = stack->next->next;
        free(stack_free);
    }
    stack_free = stack->next;
    stack->next = stack->next->next;
    free(stack_free);
}
void pop_to_postfix(lista_pok post, lista_pok stack, int x)
{
    lista_pok temp = malloc(sizeof(lista));
    temp->operacija = x;
    temp->next = post->next;
    post->next = temp;
    lista_pok temp_free = stack->next;
    temp_free->next->operacija = temp_free->operacija;
    temp_free->next->broj = temp_free->broj;
    stack->next = temp_free->next;
    free(temp_free);
}
int print(lista_pok pok)
{
    if (pok->next == NULL)
        return 0;
    while (pok->next != NULL) {
        if (pok->next->operacija != '\0')
            printf("%c ", pok->next->operacija);
        else
            printf("%d ", pok->next->broj);
        pok = pok->next;
    }
    printf("\n");
    return 0;
}
int is_number(int x)
{
    return (x < 58 && x > 47) ? 1 : 0;
}
int is_operator(int c)
{
    return ((c < 48 && c > 39 && c != 44 && c != 46) || (c == 92)) ? 1 : 0;
}
void push_int(lista_pok pok, int x, int* y)
{
    if (*y) {
        pok->next->broj = (pok->next->broj * 10) + x;
    }
    else {
        lista_pok temp = malloc(sizeof(lista));
        temp->next = pok->next;
        pok->next = temp;
        temp->broj = x;
        temp->operacija = '\0';
    }
}
void push_char(lista_pok pok, int x)
{
    lista_pok temp = malloc(sizeof(lista));
    temp->next = pok->next;
    pok->next = temp;
    temp->operacija = x;
    if (x == 43 || x == 45)
        temp->broj = 0;
    else if (x == 42 || x == 47)
        temp->broj = 1;
    else if (x == 40)
        temp->broj = 2;
    else if (x == 41)
        temp->broj = 3;
    else
        printf("ERROR\n");
}
void pop(lista_pok pok, int x)
{
    lista_pok temp, temp_free;
    temp_free = pok->next;
    temp = pok->next->next;
    temp->broj += temp_free->broj;
    free(temp_free);
}
void push_end(lista_pok post, lista_pok stack)
{
    lista_pok temp_free = NULL;
    while (stack->next != NULL) {
        lista_pok temp = malloc(sizeof(lista));
        temp->operacija = stack->next->operacija;
        temp->next = post->next;
        post->next = temp;
        stack = stack->next;
        if (temp_free != NULL)
            free(temp_free);
        temp_free = stack;
    }
}