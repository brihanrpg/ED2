#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "sequencial.h"

void ordenacao(int n) {
    FILE *arq;
    arq = fopen("informations.bin", "r+b");
    
    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    int desloc;
    information auxiliar;
    information ax;

    int h, j;

    // Determina o valor inicial de h para o algoritmo de ordenação Shell
    for (h = 1; h < n;) {
        h = 3 * h + 1;
    }

    // Executa o algoritmo de ordenação Shell
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

            // Compara as chaves dos elementos e realiza a troca se necessário
            dados.comparisons++;
            while (auxiliar.key > ax.key) {
                desloc = j * sizeof(information);
                fseek(arq, desloc, SEEK_SET);
                fwrite(&auxiliar, sizeof(information), 1, arq);
                dados.hits++;

                j = j - h;
                dados.comparisons++;
                if (j < h) {
                    break;
                }

                desloc = (j - h) * sizeof(information);
                fseek(arq, desloc, SEEK_SET);
                fread(&auxiliar, sizeof(information), 1, arq);
                dados.hits++;

                dados.comparisons++;
            }
            desloc = j * sizeof(information);
            fseek(arq, desloc, SEEK_SET);
            fwrite(&ax, sizeof(information), 1, arq);
            dados.hits++;
        }
    } while (h != 1);

    fclose(arq);
}

void sequential_access(int n, int key) {
    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();

    // Chama a função de ordenação para ordenar os dados
    ordenacao(n);

    time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparacoes: %lld\n", dados.comparisons);
    printf("Tempo: %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);

    time_begin_ind = clock();

    information x;
    int cont = 0;
    int stack_of_items = 100000 / n;
    stack_of_items = (stack_of_items < 10) ? 10 : stack_of_items;

    tipoindice tab[n];

    FILE *arq;
    arq = fopen("informations.bin", "r+b");

    if (arq == NULL) {
        printf("Erro, arquivo nao pode ser aberto!\n");
        exit(1);
    }

    cont = 0;

    // Gera a tabela de índices
    fseek(arq, 0, SEEK_SET);
    while (fread(&x, sizeof(x), 1, arq) == 1) {
        cont++;
        if (cont % stack_of_items == 1) {
            tab[cont / stack_of_items].key = x.key;
            tab[cont / stack_of_items].position = cont / stack_of_items + 1;
        }
    }

    dados.hits = 0;
    dados.comparisons = 0;
    bool get = false;
    information pagina[stack_of_items];

    int i = 0;
    while (i < n && tab[i].key <= key) {
        i++;
    }

    if (i != 0) {
        int quantitens = (i < n) ? stack_of_items : (ftell(arq) / sizeof(information)) % stack_of_items;
        long desloc = (tab[i - 1].position - 1) * stack_of_items * sizeof(information);
        fseek(arq, desloc, SEEK_SET);
        fread(&pagina[0], sizeof(information), quantitens, arq);
        dados.hits++;

        for (i = 0; i < quantitens; i++) {
            dados.comparisons++;
            if (pagina[i].key == key) {
                get = true;
                time_end_ind = clock();

                printf("\nkey: %d\n dado1: %ld\n dado2: %s\n dado3: %s\n", pagina[i].key, pagina[i].dado1, pagina[i].dado2, pagina[i].dado3);
                printf("Numero de transferencias: %lld\n", dados.hits);
                printf("Numero de comparacoes: %lld\n", dados.comparisons);
                printf("Tempo: %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
                break;
            }
        }

        if (!get) {
            printf("Chave nao encontrada!\n");
        }
    }

    fclose(arq);
}
