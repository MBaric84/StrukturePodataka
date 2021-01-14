#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS_

#define STR 256
#define N 11 

typedef struct entry {
    int mat;
    char ime[STR], prezime[STR];
    struct entry* next;
} entry;

typedef struct table {
    entry** entries;
} table;

table* create_table(void);
void insert_values(table*);
int hash(char*, int);
int collision(entry*);
void print_table(table*);
int find(table*, char*, char*);

int main()
{
    char ime[STR], prezime[STR];

    table* hashtable = create_table();
    insert_values(hashtable);
    print_table(hashtable);

    printf("Enter control c to exit\n");
    do {
        printf("\nEnter first and last name of student: ");
        scanf(" %s %s", ime, prezime);
        if (!find(hashtable, ime, prezime))
            printf("Student not in file...\n");
    } while (1);

    return 0;
}
table* create_table(void)
{
    table* hashtable = malloc(sizeof(table));
    hashtable->entries = malloc(N * sizeof(entry*));
    for (int i = 0; i < N; ++i)
        hashtable->entries[i] = NULL;
    return hashtable;
}
void insert_values(table* hashtable)
{
    FILE* ptr = fopen("datoteke/11_studenti.txt", "r");
    entry* current;
    char prez[STR], name[STR];
    int matbr, key;

    while (!feof(ptr)) {
        fscanf(ptr, "%d %s %s", &matbr, name, prez);
        key = hash(prez, 0);
        entry* temp = malloc(sizeof(entry));
        strcpy(temp->ime, name);
        strcpy(temp->prezime, prez);
        temp->mat = matbr;
        temp->next = NULL;

        if (collision(hashtable->entries[key])) {
            current = hashtable->entries[key];
            while (current->next != NULL)
                current = current->next;
            current->next = temp;
        }
        else
            hashtable->entries[key] = temp;
    }

    fclose(ptr);
}
int collision(entry* e)
{
    return (e != NULL) ? 1 : 0;
}
int hash(char* prez, int sum)
{
    for (int i = 0; i < 5 && prez[i] != '\0'; i++)
        sum += prez[i];
    return sum % N;
}
void print_table(table* hashtable)
{
    entry* current;
    for (int i = 0, j = 1; i < N; i++) {
        printf("[%d][%d]: ", i + 1, j);
        if (hashtable->entries[i] != NULL) {
            printf("%.6s\t", hashtable->entries[i]->ime);
            printf("%.6s\t", hashtable->entries[i]->prezime);
            printf("%d\t", hashtable->entries[i]->mat);
            current = hashtable->entries[i];
            while (current->next != NULL) {
                printf("[%d][%d]: ", i + 1, ++j);
                printf("%.6s\t", current->next->ime);
                printf("%.6s\t", current->next->prezime);
                printf("%d\t", current->next->mat);
                current = current->next;
            }
        }
        else
            printf("[empty]");
        printf("\n");
        j = 1;
    }
    printf("\n\n\n");
}
int find(table* hashtable, char* ime, char* prez)
{
    int key = hash(prez, 0);
    entry* current = hashtable->entries[key];
    while (current->next != NULL) {
        if (!strcmp(current->next->ime, ime) && !strcmp(current->next->prezime, prez)) {
            printf("FOUND: %d\n", current->next->mat);
            return 1;
        }
        current = current->next;
    }
    return 0;
}