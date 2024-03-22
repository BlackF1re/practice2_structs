//10. �������� ������ �������� � �����
//
//������������  ���������	����	������� � �������	������ �����������
//
//�� ������� ���������� �������� �������� � ������� ���������, ��� ��� ���������� - ������ �����������, ��������� � �������.
//������������ ����������� ����������.
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
        perror("������ �������� �����");
        return EXIT_FAILURE;
    }

    //total output:
    Drug drg;
    while (fscanf(fp, "%d %s %lf %d %s", &drg.id, drg.name, &drg.cost, &drg.isExists, drg.generics) != EOF) {
        printf("ID: %d\n", drg.id);
        printf("��������: %s\n", drg.name);
        printf("���������: %.2f\n\n", drg.cost);
        printf("�������: %d\n", drg.isExists);
        printf("�������: %s\n", drg.generics);
    }

    fclose(fp);
    //some magic
    return EXIT_SUCCESS;
}
