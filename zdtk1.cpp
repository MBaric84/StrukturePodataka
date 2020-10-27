#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define UKUPNO_BODOVA 200

struct Student {
    char first_name[50];
    char last_name[50];
    int score;
};

typedef struct Student Student;

int get_lines_count() {
    FILE* file = fopen("studenti.txt", "r");

    if (file == NULL) {
        printf("Could not open file !");
        return 0;
    }

    char n;
    int line_counter = 0;
    while (!feof(file)) {
        n = fgetc(file);
        if (n == '\n') {
            line_counter += 1;
        }
    }

    rewind(file);
    return line_counter;
}


int read_students(int size, Student* students) {
    FILE* file = fopen("studenti.txt", "r");

    if (file == NULL) {
        printf("Could not open file !");
        return 1;
    }

    int i;

    for (i = 0; i < size; i++) {
        fscanf(
            file,
            "%s %s %d",
            students[i].first_name,
            students[i].last_name,
            &students[i].score
        );
    }

    fclose(file);

    return 0;
}


int main() {
    Student* students;
    int line_number;
    int i;


    line_number = get_lines_count();
    students = (Student*)malloc(sizeof(Student) * line_number);
    read_students(line_number, students);


    float relative_score;

    printf("Ime\tPrezime\tPostotak\tBodovi\n");
    for (i = 0; i < line_number; i++) {
        relative_score = (float)students[i].score / (float)UKUPNO_BODOVA;
        printf(
            "%s\t%s\t%.2f\t%d\n",
            students[i].first_name,
            students[i].last_name,
            relative_score * 100,
            students[i].score
        );
    }

    return 0;
}