<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD (256)

typedef struct list* list_ptr;
typedef struct list {
    int broj;
    list_ptr next;
} list;

list read_file(list_ptr, char*);
list unija(list_ptr, list_ptr, list_ptr);
list presjek(list_ptr, list_ptr, list_ptr);
int sort(list_ptr);
int swap(list_ptr, list_ptr);
int combine(list_ptr);
int printlist(list_ptr);

int main(void)
{
    char dat_1[MAX_WORD] = "datoteke/L1.txt", dat_2[MAX_WORD] = "datoteke/L2.txt";
    list l1, l2, uni, inter;
    l1.next = NULL, l2.next = NULL, uni.next = NULL, inter.next = NULL;

    read_file(&l1, dat_1);
    read_file(&l2, dat_2);

    inter = presjek(&l1, &l2, &inter);
    uni = unija(&l1, &l2, &uni);

    printf("Unija:\n");
    printlist(&uni);
    printf("Presjek:\n");
    printlist(&inter);

    return 0;
}
list read_file(list_ptr ptr, char* dat)
{
    FILE* p = fopen(dat, "r");
    list_ptr temp;

    while (!feof(p)) {
        temp = (list_ptr)malloc(sizeof(list));
        fscanf(p, " %d", &temp->broj);
        temp->next = ptr->next;
        ptr->next = temp;
    }

    fclose(p);
    return *ptr;
}
list unija(list_ptr l1, list_ptr l2, list_ptr unija)
{
    unija = l1;

    while (l1->next != NULL)
        l1 = l1->next;

    l1->next = l2->next;

    if (unija->next == NULL) {
        list_ptr temp = malloc(sizeof(list));
        temp->broj = 0;
        temp->next = unija->next;
        unija->next = temp;
    }

    sort(unija);
    combine(unija);
    return *unija;
}
list presjek(list_ptr l1, list_ptr l2, list_ptr presjek)
{
    list_ptr temp, l2_head = l2;

    while (l1->next != NULL) {
        while (l2->next != NULL) {
            if (l1->next->broj == l2->next->broj) {
                temp = (list_ptr)malloc(sizeof(list));
                temp->broj = l1->next->broj;
                temp->next = presjek->next;
                presjek->next = temp;
            }
            l2 = l2->next;
        }
        l1 = l1->next;
        l2 = l2_head;
    }

    if (presjek->next == NULL) {
        temp = (list_ptr)malloc(sizeof(list));
        temp->broj = 0;
        temp->next = presjek->next;
        presjek->next = temp;
    }

    sort(presjek);
    combine(presjek);
    return *presjek;
}
int sort(list_ptr sorted)
{
    list_ptr temp = malloc(sizeof(list));
    temp = sorted;
    list_ptr temp_head = temp;

    while (sorted->next != NULL) {
        while (temp->next != NULL) {
            if (sorted->next->broj < temp->next->broj)
                swap(temp->next, sorted->next);
            temp = temp->next;
        }
        temp = temp_head;
        sorted = sorted->next;
    }

    return 0;
}
int swap(list_ptr a, list_ptr b)
{
    int temp = 0;

    temp = a->broj;
    a->broj = b->broj;
    b->broj = temp;

    return 0;
}
int combine(list_ptr ptr)
{
    ptr = ptr->next;
    list_ptr ptr_free;

    while (ptr->next != NULL) {
        if (ptr->broj == ptr->next->broj) {
            ptr_free = ptr->next;
            ptr->next = ptr->next->next;
            free(ptr_free);
        }
        else
            ptr = ptr->next;
    }
    return 0;
}
int printlist(list_ptr ptr)
{
    while (ptr->next != NULL) {
        printf("%d\t", ptr->next->broj);
        ptr = ptr->next;
    }
    printf("\n");

    return 0;
=======
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD (256)

typedef struct list* list_ptr;
typedef struct list {
    int broj;
    list_ptr next;
} list;

list read_file(list_ptr, char*);
list unija(list_ptr, list_ptr, list_ptr);
list presjek(list_ptr, list_ptr, list_ptr);
int sort(list_ptr);
int swap(list_ptr, list_ptr);
int combine(list_ptr);
int printlist(list_ptr);

int main(void)
{
    char dat_1[MAX_WORD] = "datoteke/L1.txt", dat_2[MAX_WORD] = "datoteke/L2.txt";
    list l1, l2, uni, inter;
    l1.next = NULL, l2.next = NULL, uni.next = NULL, inter.next = NULL;

    read_file(&l1, dat_1);
    read_file(&l2, dat_2);

    inter = presjek(&l1, &l2, &inter);
    uni = unija(&l1, &l2, &uni);

    printf("Unija:\n");
    printlist(&uni);
    printf("Presjek:\n");
    printlist(&inter);

    return 0;
}
list read_file(list_ptr ptr, char* dat)
{
    FILE* p = fopen(dat, "r");
    list_ptr temp;

    while (!feof(p)) {
        temp = (list_ptr)malloc(sizeof(list));
        fscanf(p, " %d", &temp->broj);
        temp->next = ptr->next;
        ptr->next = temp;
    }

    fclose(p);
    return *ptr;
}
list unija(list_ptr l1, list_ptr l2, list_ptr unija)
{
    unija = l1;

    while (l1->next != NULL)
        l1 = l1->next;

    l1->next = l2->next;

    if (unija->next == NULL) {
        list_ptr temp = malloc(sizeof(list));
        temp->broj = 0;
        temp->next = unija->next;
        unija->next = temp;
    }

    sort(unija);
    combine(unija);
    return *unija;
}
list presjek(list_ptr l1, list_ptr l2, list_ptr presjek)
{
    list_ptr temp, l2_head = l2;

    while (l1->next != NULL) {
        while (l2->next != NULL) {
            if (l1->next->broj == l2->next->broj) {
                temp = (list_ptr)malloc(sizeof(list));
                temp->broj = l1->next->broj;
                temp->next = presjek->next;
                presjek->next = temp;
            }
            l2 = l2->next;
        }
        l1 = l1->next;
        l2 = l2_head;
    }

    if (presjek->next == NULL) {
        temp = (list_ptr)malloc(sizeof(list));
        temp->broj = 0;
        temp->next = presjek->next;
        presjek->next = temp;
    }

    sort(presjek);
    combine(presjek);
    return *presjek;
}
int sort(list_ptr sorted)
{
    list_ptr temp = malloc(sizeof(list));
    temp = sorted;
    list_ptr temp_head = temp;

    while (sorted->next != NULL) {
        while (temp->next != NULL) {
            if (sorted->next->broj < temp->next->broj)
                swap(temp->next, sorted->next);
            temp = temp->next;
        }
        temp = temp_head;
        sorted = sorted->next;
    }

    return 0;
}
int swap(list_ptr a, list_ptr b)
{
    int temp = 0;

    temp = a->broj;
    a->broj = b->broj;
    b->broj = temp;

    return 0;
}
int combine(list_ptr ptr)
{
    ptr = ptr->next;
    list_ptr ptr_free;

    while (ptr->next != NULL) {
        if (ptr->broj == ptr->next->broj) {
            ptr_free = ptr->next;
            ptr->next = ptr->next->next;
            free(ptr_free);
        }
        else
            ptr = ptr->next;
    }
    return 0;
}
int printlist(list_ptr ptr)
{
    while (ptr->next != NULL) {
        printf("%d\t", ptr->next->broj);
        ptr = ptr->next;
    }
    printf("\n");

    return 0;
>>>>>>> bddda95ea745229d691cf0205ce2a0a9b41a79ee
}