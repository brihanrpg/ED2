#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "arvore_binaria.h"

void makeTree(int n) {
    FILE *arq1 = fopen("informations.bin", "rb");
    if (arq1 == NULL) {
        exit(1);
    }
    
    FILE *arq2 = fopen("dados.bin", "w+b");
    if (arq2 == NULL) {
        exit(1);
    }

    information aux;
    Node tempNode, checkNode;

    fseek(arq1, 0, SEEK_SET);
    fread(&aux, sizeof(information), 1, arq1);
    dados.hits++;

    tempNode.data = aux;
    tempNode.left = -1;
    tempNode.right = -1;

    fseek(arq2, 0, SEEK_SET);
    fwrite(&tempNode, sizeof(Node), 1, arq2);
    dados.hits++;

    for (int i = 1; i < n; i++) {
        fseek(arq1, i * sizeof(information), SEEK_SET);
        fread(&aux, sizeof(information), 1, arq1);
        dados.hits++;

        tempNode.data = aux;
        tempNode.left = -1;
        tempNode.right = -1;

        fseek(arq2, i * sizeof(Node), SEEK_SET);
        fwrite(&tempNode, sizeof(Node), 1, arq2);
        dados.hits++;

        int indice = 0;
        bool found = false;

        while (!found) {
            fseek(arq2, indice * sizeof(Node), SEEK_SET);
            fread(&checkNode, sizeof(Node), 1, arq2);
            dados.hits++;
            dados.comparisons++;

            if (tempNode.data.key > checkNode.data.key) {
                dados.comparisons++;
                if (checkNode.right == -1) {
                    checkNode.right = i;
                    found = true;
                } else {
                    indice = checkNode.right;
                }
            } else {
                dados.comparisons++;
                if (checkNode.left == -1) {
                    checkNode.left = i;
                    found = true;
                } else {
                    indice = checkNode.left;
                }
            }
        }

        fseek(arq2, indice * sizeof(Node), SEEK_SET);
        fwrite(&checkNode, sizeof(Node), 1, arq2);
        dados.hits++;
    }

    fclose(arq1);
    fclose(arq2);
}

void arvore_bin(int n, int key) {
    clock_t time_begin_ind = clock();
    makeTree(n);
    clock_t time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparacoes: %lld\n", dados.comparisons);
    printf("Tempo: %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);

    time_begin_ind = clock();
    dados.hits = 0;
    dados.comparisons = 0;

    FILE *arq = fopen("dados.bin", "rb");
    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    int indice = 0;
    bool found = false;
    Node checkNode;

    while (!found) {
        fseek(arq, indice * sizeof(Node), SEEK_SET);
        fread(&checkNode, sizeof(Node), 1, arq);
        dados.hits++;
        dados.comparisons++;

        if (key == checkNode.data.key) {
            found = true;
        } else if (key > checkNode.data.key) {
            dados.comparisons++;
            if (checkNode.right == -1) {
                break;
            } else {
                indice = checkNode.right;
            }
        } else {
            dados.comparisons++;
            if (checkNode.left == -1) {
                break;
            } else {
                indice = checkNode.left;
            }
        }
    }

    time_end_ind = clock();

    if (found) {
        printf("\nkey : %d\n dado1 : %ld\n dado2 : %s\n dado3 : %s\n", checkNode.data.key, checkNode.data.dado1, checkNode.data.dado2, checkNode.data.dado3);
        printf("Numero de transferencias: %lld\n", dados.hits);
        printf("Numero de comparacoes: %lld\n", dados.comparisons);
        printf("Tempo: %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    } else {
        printf("key nao encontrada!\n");
    }

    fclose(arq);
}
