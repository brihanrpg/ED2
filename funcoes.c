#include "funcoes.h"

void create_file(int amount, int situacao, int key) {
    int i, position;

    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();  // Inicia a contagem de tempo

    if (key) {
        printf("keys of informations:\n");
    }

    FILE *arquivo = fopen("informations.bin", "wb");  // Abre o arquivo binário para escrita

    information info;
    info.dado1 = 0;

    // Preenche o campo "dado2" com caracteres aleatórios
    for (int j = 0; j < 1000; j++) {
        info.dado2[j] = 'a' + (char)(rand() % 26);
    }
    info.dado2[1000] = '\0';

    // Preenche o campo "dado3" com caracteres aleatórios
    for (int j = 0; j < 5000; j++) {
        info.dado3[j] = 'a' + (char)(rand() % 26);
    }
    info.dado3[5000] = '\0';

    switch (situacao) {
        case 1:
            for (i = 1; i <= amount; i++) {
                info.key = i;
                if (key) {
                    printf("%d ", i);
                }
                fwrite(&info, sizeof(information), 1, arquivo);  // Escreve a informação no arquivo
            }
            break;
        case 2:
            for (i = amount; i >= 1; i--) {
                info.key = i;
                if (key) {
                    printf("%d ", i);
                }
                fwrite(&info, sizeof(information), 1, arquivo);  // Escreve a informação no arquivo
            }
            break;
        case 3:
            srand(time(NULL));
            char *score = malloc(sizeof(char) * (amount + 1));
            memset(score, '0', amount * sizeof(char));
            score[amount] = '\0';

            i = 1;
            while (i <= amount) {
                position = rand() % amount + 1;
                if (score[position - 1] == '0') {
                    score[position - 1] = '1';
                    info.key = position;
                    printf("%d ", position);
                    fwrite(&info, sizeof(information), 1, arquivo);  // Escreve a informação no arquivo
                    i++;
                }
            }

            free(score);
            break;
        default:
            printf("\nTeste inexistente!\n");
            break;
    }

    fclose(arquivo);  // Fecha o arquivo

    time_end_ind = clock();  // Finaliza a contagem de tempo
    printf("Numero de transferencias: %d\n", amount);
    printf("Numero de comparacoes: %d\n", amount);
    printf("Tempo: %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);  // Calcula e exibe o tempo de execução
}
