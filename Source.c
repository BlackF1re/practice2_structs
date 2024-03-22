//10. Исходные данные хранятся в файле
//
//Наименование  лекарства	Цена	Отметка о наличии	список заменителей
//
//По запросу покупателя выдавать сведения о наличии лекарства, при его отсутствии - список заменителей, имеющихся в наличии.
//Использовать структурные переменные.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    int id;
    char name[50];
    float cost;
    int is_exists;
    char generics[100];
} Drug;

void read_drugs_from_file(const char* filename, Drug** drugs, int* count) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    *drugs = NULL;
    *count = 0;

    Drug drg;
    while (fscanf(fp, "%d %s %f %d %s", &drg.id, drg.name, &drg.cost, &drg.is_exists, drg.generics) != EOF) {
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

void print_drugs(Drug* drugs, int count) {
    for (int i = 0; i < count; i++) {
        printf("ID:\t%d\n", drugs[i].id);
        printf("Название:\t%s\n", drugs[i].name);
        printf("Стоимость:\t%.2f\n", drugs[i].cost);
        if(drugs[i].is_exists == 1)
            printf("Наличие:\tДа.\n");
        else
        {
            printf("Наличие:\tНет.\n");
        }

        printf("Аналоги:\t%s\n", drugs[i].generics);
        printf("--------------------------------------------------\n");
    }
}

int main() {
    SetConsoleOutputCP(1251);
    Drug* drugs = NULL;
    int count = NULL;

    read_drugs_from_file("drugs.txt", &drugs, &count);
    print_drugs(drugs, count);

    free(drugs);
    return EXIT_SUCCESS;
}
