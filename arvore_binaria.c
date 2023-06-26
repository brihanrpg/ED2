#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "arvore_binaria.h"

void makeTree(int n) {
    // Open the used files
    FILE *arq1, *arq2;

    arq1 = fopen("informations.bin", "rb");
    arq2 = fopen("dados.bin", "r+b");

    if (arq1 == NULL)
        exit(1);

    arq2 = fopen("dados.bin", "w+b");

    // In case of no finded file
    if (arq2 == NULL) {
        arq2 = fopen("dados.bin", "wb");
        fclose(arq2);
        arq2 = fopen("dados.bin", "r+b");
        if (arq2 == NULL)
            exit(1);
    }

    information aux;
    Node tempNode, checkNode;

    fseek(arq1, 0 * sizeof(information), SEEK_SET);
    fread(&aux, sizeof(information), 1, arq1);
    dados.hits++;

    tempNode.data = aux;
    tempNode.left = -1;
    tempNode.right = -1;

    fseek(arq2, 0 * sizeof(Node), SEEK_SET);
    fwrite(&tempNode, sizeof(Node), 1, arq2);
    dados.hits++;

    for (int i = 1; i < n; i++) {
        // Parse the file
        fseek(arq1, i * sizeof(information), SEEK_SET);
        fread(&aux, sizeof(information), 1, arq1);
        dados.hits++;

        tempNode.data = aux;
        tempNode.left = -1;
        tempNode.right = -1;

        // Write the data at tree
        fseek(arq2, i * sizeof(Node), SEEK_SET);
        fwrite(&tempNode, sizeof(Node), 1, arq2);
        dados.hits++;

        int indice = 0;

        // Set the sons
        while (1) {
            fseek(arq2, indice * sizeof(Node), SEEK_SET);
            fread(&checkNode, sizeof(Node), 1, arq2);
            dados.hits++;
            dados.comparisons++;

            // In case of son bigger than father
            if (tempNode.data.key > checkNode.data.key) {
                if (checkNode.right == -1) {
                    checkNode.right = i;
                    dados.comparisons++;
                    break;
                } else {
                    indice = checkNode.right;
                    dados.comparisons++;
                }
            }

            // In case of son smaller than father
            else {
                if (checkNode.left == -1) {
                    checkNode.left = i;
                    dados.comparisons++;
                    break;
                } else {
                    indice = checkNode.left;
                    dados.comparisons++;
                }
            }
        }

        fseek(arq2, indice * sizeof(Node), SEEK_SET);
        fwrite(&checkNode, sizeof(Node), 1, arq2);
        dados.hits++;
    }
    fclose(arq2);
}

void arvore_bin(int n, int key) {
    // Initialize the clock
    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();

    // Make the tree to search
    makeTree(n);

    time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparisons: %lld\n", dados.comparisons);
    dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    printf("Tempo : %lfs\n", dados.time);

    time_begin_ind = clock();

    // Initialize the datas of search
    dados.hits = 0;
    dados.comparisons = 0;

    FILE *arq = fopen("dados.bin", "rb");
    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    int indice = 0;
    _Bool get = false;
    Node checkNode;

    while (1) {
        fseek(arq, indice * sizeof(Node), SEEK_SET);
        fread(&checkNode, sizeof(Node), 1, arq);
        dados.hits++;

        dados.comparisons++;

        // In case of find the correct key
        if (key == checkNode.data.key) {
            get = true;
            dados.comparisons++;
            break;
        }

        // In case of actual key is bigger than choosed
        else if (key > checkNode.data.key) {
            // In case of a leaf node
            dados.comparisons++;
            if (checkNode.right == -1) {

                break;
            } else {
                indice = checkNode.right;
            }
        }

        // In case of actual key is smaller than choosed
        else {
            // In case of a leaf node
            if (checkNode.left == -1) {
                break;
            } else {
                indice = checkNode.left;
            }
        }
    }

    // Turn off the clock
    time_end_ind = clock();

    // Successful search
    if (get) {
        printf("\nkey : %d\n dado1 : %ld\n dado2 : %s\n dado3 : %s\n", checkNode.data.key, checkNode.data.dado1,
               checkNode.data.dado2, checkNode.data.dado3);
        printf("Numero de transferencias: %lld\n", dados.hits);
        printf("Numero de comparisons: %lld\n", dados.comparisons);
        dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
        printf("Tempo : %lfs\n", dados.time);
    }
    // Wrong search
    else
        printf("key nao encontrada!\n");

    fclose(arq);
}

