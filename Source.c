//10. �������� ������ �������� � �����
//
//������������  ���������	����	������� � �������	������ �����������
//
//�� ������� ���������� �������� �������� � ������� ���������, ��� ��� ���������� - ������ �����������, ��������� � �������.
//������������ ����������� ����������.

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
        printf("������ �������� ����������:\n");
        for (int i = 0; i < count; i++) {
            printf("ID:\t%d\n", drugs[i].id);
            printf("��������:\t%s\n", drugs[i].name);
            printf("���������:\t%.2f\n", drugs[i].cost);

            if (drugs[i].isInStock == 1)
                printf("�������:\t��.\n");
            else
            {
                printf("�������:\t���.\n");
            }

            printf("�������:\t%s\n", drugs[i].generics);
            printf("--------------------------------------------------\n");
        }
        break;

    case 1://only in stock output
        printf("��������� � �������:\n");
        for (int i = 0; i < count; i++) {
            if (drugs[i].isInStock == 1) {
                printf("ID:\t%d\n", drugs[i].id);
                printf("��������:\t%s\n", drugs[i].name);
                printf("���������:\t%.2f\n", drugs[i].cost);
                printf("�������:\t%s\n", drugs[i].generics);
                printf("--------------------------------------------------\n");
            }
        }
        break;

    default:
        printf("������������ �����.\n");
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
    printf("���������� ������ �������� ���������� ��� ������ ��������� � �������?\n0 - ������ �������� ����������, 1 - ������ � �������\n");
    isDigit = scanf("%d", &choice);
    if (isDigit != 1)
        error();
    print_drugs(drugs, count, choice);

    free(drugs);
    return 0;
}