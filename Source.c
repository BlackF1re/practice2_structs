//10. Исходные данные хранятся в файле
//
//Наименование  лекарства	Цена	Отметка о наличии	список заменителей
//
//По запросу покупателя выдавать сведения о наличии лекарства, при его отсутствии - список заменителей, имеющихся в наличии.
//Использовать структурные переменные.

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float cost;
    int isInStock;
    char generics[100];
} Drug;

static void read_drugs_from_file(const char* filename, Drug** drugs, int* count) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        error();

    *drugs = NULL;
    *count = 0;

    Drug drg;
    while (fscanf(fp, "%d,%[^,],%f,%d,%[^\n]\n", &drg.id, drg.name, &drg.cost, &drg.isInStock, drg.generics) != EOF) {
        *count = *count + 1;
        *drugs = realloc(*drugs, *count * sizeof(Drug));
        if (*drugs == NULL) {
            perror("Error allocating memory");
            return;
        }
        (*drugs)[*count - 1] = drg;
    }
    fclose(fp);
}

static void print_drugs(Drug* drugs, int count, int isSortInStock) {
    switch (isSortInStock) {
    case 0://not sorted output
        printf("Полный перечень препаратов:\n");
        for (int i = 0; i < count; i++) {
            printf("ID:\t%d\n", drugs[i].id);
            printf("Название:\t%s\n", drugs[i].name);
            printf("Стоимость:\t%.2f\n", drugs[i].cost);

            if (drugs[i].isInStock == 1)
                printf("Наличие:\tДа.\n");
            else
            {
                printf("Наличие:\tНет.\n");
            }

            printf("Аналоги:\t%s\n", drugs[i].generics);
            printf("--------------------------------------------------\n");
        }
        break;

    case 1://only in stock output
        printf("Препараты в наличии:\n");
        for (int i = 0; i < count; i++) {
            if (drugs[i].isInStock == 1) {
                printf("ID:\t%d\n", drugs[i].id);
                printf("Название:\t%s\n", drugs[i].name);
                printf("Стоимость:\t%.2f\n", drugs[i].cost);
                printf("Аналоги:\t%s\n", drugs[i].generics);
                printf("--------------------------------------------------\n");
            }
        }
        break;

    default:
        printf("Недопустимый выбор.\n");
    }
}

int error() {
    printf("error");
    exit;
}

void main() {
    SetConsoleOutputCP(1251);
    Drug* drugs = NULL;
    int count = NULL;
    int choice = NULL;
    int isDigit = 0;
    read_drugs_from_file("drugs.csv", &drugs, &count);
    printf("Отобразить полный перечень препаратов или только препараты в наличии?\n0 - полный перечень препаратов, 1 - только в наличии\n");
    isDigit = scanf("%d", &choice);
    if (isDigit != 1)
        error();
    print_drugs(drugs, count, choice);

    free(drugs);
    return 0;
}