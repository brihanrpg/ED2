#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "sequencial.h"
#include <math.h>

void ordenacao(int n) {
    FILE *arq;
    arq = fopen("informations.bin", "r+b");

    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    int desloc;
    information auxiliar;
    information auxiliar2;
    information ax, l;

    int h, j;

    for (h = 1; h < n;) {
        h = 3 * h + 1;
    }

    do {
        h = (h - 1) / 3;
        for (int i = h; i < n; i++) {
            desloc = i * sizeof(information);
            fseek(arq, desloc, SEEK_SET);
            fread(&ax, sizeof(information), 1, arq);
            dados.hits++;

            j = i;

            desloc = (j - h) * sizeof(information);
            fseek(arq, desloc, SEEK_SET);
            fread(&auxiliar, sizeof(information), 1, arq);
            dados.hits++;

            while (auxiliar.key > ax.key) {
                dados.comparisons++;

                desloc = (j) * sizeof(information);

                fseek(arq, desloc, SEEK_SET);
                fwrite(&auxiliar, sizeof(information), 1, arq);
                dados.hits++;

                j = j - h;
                if (j < h) {
                    dados.comparisons++;
                    break;
                }

                desloc = (j - h) * sizeof(information);
                fseek(arq, desloc, SEEK_SET);
                fread(&auxiliar, sizeof(information), 1, arq);
                dados.hits++;
            }
            desloc = (j) * sizeof(information);
            fseek(arq, desloc, SEEK_SET);
            fwrite(&ax, sizeof(information), 1, arq);
            dados.hits++;
        }
    } while (h != 1);
    fclose(arq);
}

void sequential_access(int n, int key) {
    //Initialize the clock
    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();

    ordenacao(n);

    time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparisons: %lld\n", dados.comparisons);
    dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    printf("Tempo : %lfs\n", dados.time);
    time_begin_ind = clock();

    information x;
    int pos, cont;
    information ax;
    int tam = 100 * 100000 / n < 10;
    if (tam < 10)
        tam = 10;
    int stack_of_items = tam;
    tipoindice tab[n];

    FILE *arq;
    arq = fopen("informations.bin", "r+b");

    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    // gera a tab de índice das páginas
    cont = 0;
    pos = 0;
    fseek(arq, 0 * sizeof(information), SEEK_SET);
    while (fread(&x, sizeof(x), 1, arq) == 1) {
        cont++;
        dados.hits++;
        if (cont % stack_of_items == 1) {
            tab[pos].key = x.key;
            tab[pos].position = pos + 1;
            pos++;
        }
    }

    //Initialize the datas of search
    dados.hits = 0;
    dados.comparisons = 0;

    _Bool get = false;

    information pagina[stack_of_items];

    int i, quantitens;
    long desloc;

    i = 0;
    while (i < pos && tab[i].key <= key) {
        i++;
        dados.comparisons++;
    }

    if (i != 0) {
        if (i < pos)
            quantitens = stack_of_items;
        else {
            fseek(arq, 0, SEEK_END);
            quantitens = (ftell(arq) / sizeof(information)) % stack_of_items;
        }
        desloc = (tab[i - 1].position - 1) * stack_of_items * sizeof(information);
        fseek(arq, desloc, SEEK_SET);
        fread(&pagina[0], sizeof(information), stack_of_items, arq);

        dados.hits++;

        for (i = 0; i < quantitens; i++) {
            if (pagina[i].key == key) {
                dados.comparisons++;
                get = true;

                //Turn off the clock
                time_end_ind = clock();

                printf("\nkey : %d\n dado1 : %ld\n dado2 : %s\n dado3 : %s\n", pagina[i].key, pagina[i].dado1, pagina[i].dado2, pagina[i].dado3);
                printf("Numero de transferencias: %lld\n", dados.hits);
                printf("Numero de comparisons: %lld\n", dados.comparisons);
                dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
                printf("Tempo : %lfs\n", dados.time);
                break;
            }
        }

        if (!get)
            printf("key nao encontrada!\n");
    }

    fclose(arq);
}
