#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD (256)

typedef struct person node;
struct person {
    char ime[MAX_WORD];
    char prez[MAX_WORD];
    int godina;
    struct person* next;
};

void unos(char*, char*, int*);
node* napravi_node(char*, char*, int*);
node* dodaj_na_pocetku(node**, node*);
node* dodaj_na_kraju(node**, node*);
void ispis(node*);
node* pronalazi_element(node*, char[MAX_WORD], int*);
int usporedi(char[MAX_WORD], char[MAX_WORD]);
void brisi_element(node**, node*);
void unesi_nakon(node*, node*);
void unesi_prije(node*, node*, node*);
void sort(node*);
void write(FILE*, node*);
void read(FILE*, node**);
void swap(node*, node*);

int main()
{
    FILE* ptr;
    node* head = NULL;
    node* n, * n2;
    int z, error = 1;
    char x[MAX_WORD], y[MAX_WORD], c;

    do {
        printf("\nA - Dodaj novu osobu na pocetku liste\nB - Ispisi listu\nC - Dodaj osobu na kraju liste\nD - Pretrazi osobu po prezimenu\nE - Obrisi osobu sa liste\nF - Dodaj iducu osobu nakon jedne osobe\nG - Dodaj osobu prije druge osobe\nH - Sortiraj listu po prezimenima\nI - Upisi listu u datoteku\nJ - Citaj listu iz datoteke\nQ - Quit program\n\n");

        printf("Unesite odabir: ");
        scanf(" %c", &c);

        switch (c) {
        case 'A':
        case 'a':
            unos(x, y, &z);
            n = napravi_node(x, y, &z);
            dodaj_na_pocetku(&head, n);
            break;
        case 'B':
        case 'b':
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            printf("\n");
            ispis(head);
            break;
        case 'C':
        case 'c':
            unos(x, y, &z);
            n = napravi_node(x, y, &z);
            dodaj_na_kraju(&head, n);
            break;
        case 'D':
        case 'd':
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            printf("Unesite prezime: ");
            scanf(" %s", x);
            n = pronalazi_element(head, x, &error);
            if (error)
                printf("/*\t%s %s\t%d\t*/\n", n->ime, n->prez, n->godina);
            break;
        case 'E':
        case 'e':
            printf("\nUnesite prezime: ");
            scanf(" %s", x);
            n = pronalazi_element(head, x, &error);
            brisi_element(&head, n);
            break;
        case 'F':
        case 'f':
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            unos(x, y, &z);
            n = napravi_node(x, y, &z);
            printf("Prezime osobe koje ce unosen osoba slijediti: ");
            scanf(" %s", x);
            n2 = pronalazi_element(head, x, &error);
            if (error)
                unesi_nakon(n2, n);
            break;
        case 'G':
        case 'g':
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            unos(x, y, &z);
            n = napravi_node(x, y, &z);
            printf("Prezime osobe koje ce unosen osoba prethoditi: ");
            scanf(" %s", x);
            n2 = pronalazi_element(head, x, &error);
            if (error)
                unesi_prije(head, n2, n);
            break;
        case 'H':
        case 'h':
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            sort(head);
            break;
        case 'I':
        case 'i':
            ptr = fopen("write_to.txt", "w");
            write(ptr, head);
            if (head == NULL) {
                printf("\nList je prazan...\n\n");
                break;
            }
            break;
        case 'J':
        case 'j':
            ptr = fopen("read_from.txt", "r");
            read(ptr, &head);
            break;
        case 'Q':
        case 'q':
            continue;
        default:
            printf("\nPonovno unesite odabir...\n\n");
            break;
        }

    } while (c != 'q' && c != 'Q');


    return 0;
}
void unos(char* x, char* y, int* z)
{
    printf("\nUnesi ime: ");
    scanf(" %s", x);
    printf("Unesi prezime: ");
    scanf(" %s", y);
    printf("Unesi godinu rodenja: ");
    scanf(" %d", z);
}
node* napravi_node(char* x, char* y, int* z)
{
    node* tmp = malloc(sizeof(node));
    strcpy(tmp->ime, x);
    strcpy(tmp->prez, y);
    tmp->godina = *z;
    tmp->next = NULL;

    return tmp;
}
void ispis(node* head)
{
    node* tmp = head;

    while (tmp != NULL) {
        printf("/*\t%s %s\t%d\t*/\n", tmp->ime, tmp->prez, tmp->godina);
        tmp = tmp->next;
    }
}
node* dodaj_na_pocetku(node** head, node* n)
{
    n->next = *head;
    *head = n;
    return n;
}
node* dodaj_na_kraju(node** head, node* n)
{
    if (*head == NULL)
        dodaj_na_pocetku(head, n);
    else {
        node* tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = n;
        n->next = NULL;
    }

    return n;
}
node* pronalazi_element(node* head, char ime[MAX_WORD], int* error)
{
    int br = 0;
    *error = 1;
    node* n=NULL;
    for (node* tmp = head; tmp != NULL; tmp = tmp->next) {
        if (usporedi(tmp->prez, ime) && strlen(tmp->prez) == strlen(ime)) {
            n = tmp;
            br++;
        }
    }
    if (br > 1)
        printf("\nMore than one person matched your search..\n");
    else if (br == 0) {
        printf("\nNo items matched your query...\n");
        *error = 0;
        return NULL;
    }

    return n;
}
int usporedi(char str[MAX_WORD], char str2[MAX_WORD])
{
    for (int i = 0; str[i]; i++) {
        if (tolower(str[i]) == tolower(str2[i]))
            continue;
        else
            return 0;
    }
    return 1;
}
void brisi_element(node** head, node* n)
{
    node* tmp = *head;

    if (*head == n) {
        *head = n->next;
        free(n);
        return;
    }

    while (tmp->next != n)
        tmp = tmp->next;

    tmp->next = tmp->next->next;
    free(n);
    return;
}
void unesi_nakon(node* current, node* new)
{
    new->next = current->next;
    current->next = new;
}
void unesi_prije(node* head, node* current, node* new)
{
    node* tmp = head;

    while (tmp->next != current)
        tmp = tmp->next;

    tmp->next = new;
    new->next = current;
}
void write(FILE* ptr, node* head)
{
    node* n = head;

    while (n != NULL) {
        fprintf(ptr, "%s %s\t%d\n", n->ime, n->prez, n->godina);
        n = n->next;
    }
}
void read(FILE* ptr, node** head)
{
    //*head = NULL;
    node* n;
    int br = 0, z;
    char a, c, x[MAX_WORD], y[MAX_WORD];

    while ((c = fgetc(ptr)) != EOF)
        if (c == '\n')
            br++;
    rewind(ptr);

    for (int i = 0; i < br; i++) {
        fscanf(ptr, "%s %s %d", x, y, &z);
        n = napravi_node(x, y, &z);
        dodaj_na_kraju(head, n);
    }
}
void sort(node* head)
{
    node* val;
    for (node* tmp = head; tmp != NULL; tmp = tmp->next) {
        for (node* nxt = head; nxt->next != NULL; nxt = nxt->next) {
            if ((nxt->next != NULL) && (strcmp(nxt->prez, nxt->next->prez) > 0))
                swap(nxt, nxt->next);
        }
    }
}
void swap(node* n1, node* n2)
{
    char temp[MAX_WORD];
    int tmp;

    strcpy(temp, n1->ime);
    strcpy(n1->ime, n2->ime);
    strcpy(n2->ime, temp);
    strcpy(temp, n1->ime);

    strcpy(temp, n1->prez);
    strcpy(n1->prez, n2->prez);
    strcpy(n2->prez, temp);
    strcpy(temp, n1->prez);

    tmp = n1->godina;
    n1->godina = n2->godina;
    n2->godina = tmp;
}