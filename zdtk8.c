#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 64

typedef struct directory* pok;
typedef struct directory {
    char ime[M];
    pok child;
    pok next;
} directory;

typedef struct stack* stack_pok;
typedef struct stack {
    pok adresa;
    stack_pok next;
} stack;

int unos(char*);
int mkdir(pok, char*);
int mkchild(pok, char*);
int exists(pok, char*);
int empty_dir(pok);
int empty_stack(stack_pok);
int print(pok);
void print_stack(stack_pok);
void push(stack_pok, pok);
pok pop(stack_pok);

int main()
{
    directory dir; dir.next = NULL; dir.child = NULL; strcpy(dir.ime, "~");
    pok current = &dir;
    stack stog; stog.next = NULL;
    char c[M], ime[M];
    int d = 1, i = 0, empty;

    do {
        if (strcmp(current->ime, "~"))
            printf("\n%s: ", current->ime);
        else
            printf("\n%s ", current->ime);


        if (unos(c)) {
            unos(ime);
            empty = 0;
        }
        else {
            ime[0] = '\0';
            empty = 1;
        }

        if (!strcmp(c, "mkdir")) {
            if (empty)
                printf("\nDirectory must have a ime\n");
            else if (empty_dir(current))
                mkchild(current, ime);
            else if (exists(current, ime))
                printf("\nA directory with that ime already exists in current directory\n");
            else
                mkdir(current, ime);
        }
        else if (!strcmp(c, "ls")) {
            if (empty_dir(current))
                printf("\nempty...\n");
            else
                print(current);
        }
        else if ((!strcmp(c, "cd")) && (!empty)) {
            if (!exists(current, ime))
                printf("\nNo such file or directory\n");
            else {
                push(&stog, current);
                current = current->child;
                while (strcmp(current->ime, ime))
                    current = current->next;
            }
        }
        else if ((!strcmp(c, "cd")) && empty) {
            if (empty_stack(&stog)) {
                printf("\nin head directory\n");
            }
            else
                current = pop(&stog);
        }
        else if ((!strcmp(c, "clear")) || (!strcmp(c, "c"))) {
            system("clear");
        }
        else if (!strcmp(c, "pwd")) {
            print_stack(&stog);
            printf("%s\n", current->ime);
        }
        else if (!strcmp(c, "q"))
            d = 0;
        else
            printf("command not found\n");
    } while (d);

    return 0;
}
int unos(char* string)
{
    char c; int i = 0;
    while ((c = fgetc(stdin)) != '\n' && c != ' ') {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    if (c == '\n')
        i = 0;
    return i;
}
int mkchild(pok dir, char* ime)
{
    pok kid = malloc(sizeof(directory));
    strcpy(kid->ime, ime);
    kid->next = NULL;
    kid->child = NULL;
    dir->child = kid;
    return 0;
}
int mkdir(pok root, char* ime)
{
    root = root->child;
    pok dir = malloc(sizeof(directory));
    strcpy(dir->ime, ime);
    dir->next = root->next;
    root->next = dir;
    dir->child = NULL;
    return 0;
}
int print(pok p)
{
    pok dir = p->child;
    while (dir != NULL) {
        printf("\n%s\n", dir->ime);
        dir = dir->next;
    }
    return 0;
}
int exists(pok pok, char* ime)
{
    pok = pok->child;
    while (pok != NULL) {
        if (!strcmp(pok->ime, ime))
            return 1;
        pok = pok->next;
    }
    return 0;
}
int empty_dir(pok pok)
{
    if (pok->child == NULL)
        return 1;
    return 0;
}
int empty_stack(stack_pok pok)
{
    return (pok->next == NULL) ? 1 : 0;
}
void push(stack_pok stack, pok dir)
{
    stack_pok temp = malloc(sizeof(stack));
    temp->adresa = dir;
    temp->next = stack->next;
    stack->next = temp;
}
pok pop(stack_pok stack)
{
    pok dir = stack->next->adresa;
    stack_pok stack_free = stack->next;
    stack->next = stack->next->next;
    free(stack_free);
    return dir;
}
void print_stack(stack_pok pok)
{
    if (pok == NULL)
        return;
    print_stack(pok->next);
    if (strlen(pok->adresa->ime))
        printf("%s/", pok->adresa->ime);
}