//10. Исходные данные хранятся в файле
//
//Наименование  лекарства	Цена	Отметка о наличии	список заменителей
//
//По запросу покупателя выдавать сведения о наличии лекарства, при его отсутствии - список заменителей, имеющихся в наличии.
//Использовать структурные переменные.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float cost;
    int isExists;
    char generics[100];
} Drug;

int main() {
    FILE* fp = fopen("drugs.txt", "r");
    if (fp == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    //total output:
    Drug drg;
    while (fscanf(fp, "%d %s %lf %d %s", &drg.id, drg.name, &drg.cost, &drg.isExists, drg.generics) != EOF) {
        printf("ID: %d\n", drg.id);
        printf("Название: %s\n", drg.name);
        printf("Стоимость: %.2f\n\n", drg.cost);
        printf("Наличие: %d\n", drg.isExists);
        printf("Аналоги: %s\n", drg.generics);
    }

    fclose(fp);
    //some magic
    return EXIT_SUCCESS;
}
