#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD (256)

typedef struct poly* poly_ptr;
typedef struct poly {
    int coeff;
    int exp;
    poly_ptr next;
} poly;

poly read_data(poly_ptr, char*);
poly add(poly_ptr, poly_ptr, poly_ptr);
poly mult(poly_ptr, poly_ptr, poly_ptr);
void print_list(poly_ptr);
void sort(poly_ptr);
void swap(poly_ptr, poly_ptr);
void combine(poly_ptr);
int is_number(int);

int main(void)
{
    char dat_1[MAX_WORD] = "datoteke/prvi.txt", dat_2[MAX_WORD] = "datoteke/drugi.txt";

    poly_ptr p_1 = malloc(sizeof(poly)), p_2 = malloc(sizeof(poly));
    p_1->next = NULL, p_2->next = NULL;
    poly p1, p2, zbr, pro;
    p1.next = NULL, p2.next = NULL, zbr.next = NULL, pro.next = NULL;

    p1 = read_data(&p1, dat_1);
    p2 = read_data(&p2, dat_2);
    p_2 = &p2;
    p_1 = &p1;

    zbr = add(p_1, p_2, &zbr);
    pro = mult(p_1, p_2, &pro);

    printf("Prvi polinom:  ");   print_list(p_2);
    printf("Drugi polinom:  ");   print_list(p_1);
    printf("Zbroj polinoma:  ");   print_list(&zbr);
    printf("Umnozak polinoma:  ");   print_list(&pro);

    return 0;
}
poly read_data(poly_ptr n, char* dat)
{
    FILE* ptr = NULL;
    ptr = fopen(dat, "r");

    char c;
    int br = 0, temp = 0, x = 0, * y;

    poly_ptr temp_ptr;
    y = (int*)malloc(sizeof(int));

    while ((c = fgetc(ptr)) != EOF) {
        if (is_number(c)) {
            if (br) {
                temp *= 10;
                temp += c - 48;
            }
            else {
                temp = c - 48;
                br++;
            }
        }
        else if (br > 0) {
            x++;
            y = (int*)realloc(y, x * sizeof(int));
            y[x - 1] = temp;
            temp = 0;
            br = 0;
        }
        else {
            br = 0;
        }
    }
    x++;
    y = (int*)realloc(y, x * sizeof(int));
    y[x - 1] = temp;

    for (int i = 0; i < x; i += 2) {
        temp_ptr = (poly_ptr)malloc(sizeof(poly));
        temp_ptr->coeff = y[i];
        temp_ptr->exp = y[i + 1];
        temp_ptr->next = n->next;
        n->next = temp_ptr;

    }

    fclose(ptr);
    return *n;
}
poly add(poly_ptr p1, poly_ptr p2, poly_ptr zbr)
{
    poly_ptr temp;

    while (p1->next != NULL) {
        temp = (poly_ptr)malloc(sizeof(poly));
        temp->coeff = p1->next->coeff;
        temp->exp = p1->next->exp;
        temp->next = zbr->next;
        zbr->next = temp;

        temp = (poly_ptr)malloc(sizeof(poly));
        temp->coeff = p2->next->coeff;
        temp->exp = p2->next->exp;
        temp->next = zbr->next;
        zbr->next = temp;

        p1 = p1->next;
        p2 = p2->next;
    }
    sort(zbr);
    combine(zbr);
    return *zbr;
}
poly mult(poly_ptr p1, poly_ptr p2, poly_ptr pro)
{
    poly_ptr temp, p2_head;
    p2_head = p2;

    while (p1->next != NULL) {
        while (p2->next != NULL) {
            temp = (poly_ptr)malloc(sizeof(poly));
            temp->coeff = p1->next->coeff * p2->next->coeff;
            temp->exp = p1->next->exp + p2->next->exp;
            temp->next = pro->next;
            pro->next = temp;

            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = p2_head;
    }

    sort(pro);
    combine(pro);
    return *pro;
}
void print_list(poly_ptr p)
{
    int i = 0;

    while (p->next != NULL) {
        if (i)
            printf(" + ");
        if (p->next->exp == 1)
            printf("%dx", p->next->coeff);
        else if (!p->next->exp)
            printf("%d", p->next->coeff);
        else
            printf("(%dx)^%d", p->next->coeff, p->next->exp);

        p = p->next;
        i++;
    }
    printf("\n");
}
void sort(poly_ptr sorted)
{
    poly_ptr temp = malloc(sizeof(poly));
    temp = sorted;
    poly_ptr temp_head = temp;

    while (sorted->next != NULL) {
        while (temp->next != NULL) {
            if (sorted->next->exp < temp->next->exp)
                swap(temp->next, sorted->next);
            temp = temp->next;
        }
        temp = temp_head;
        sorted = sorted->next;
    }
    return;
}
void swap(poly_ptr a, poly_ptr b)
{
    int temp = 0;

    temp = a->exp;
    a->exp = b->exp;
    b->exp = temp;

    temp = a->coeff;
    a->coeff = b->coeff;
    b->coeff = temp;

    return;
}
void combine(poly_ptr ptr)
{
    ptr = ptr->next;

    while (ptr->next != NULL) {
        if (ptr->exp == ptr->next->exp) {
            ptr->coeff += ptr->next->coeff;
            ptr->next = ptr->next->next;
        }
        else
            ptr = ptr->next;
    }
    return;
}
int is_number(int x)
{
    return (x < 58 && x > 47) ? 1 : 0;
}