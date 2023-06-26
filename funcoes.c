#include "funcoes.h"


void create_file(int amount, int situacao, int key){  //Fun��o de preencimento de arquivo
    int j,i,position;

    clock_t time_begin_ind, time_end_ind;

    time_begin_ind = clock();

    if (key)
        printf("keys of informations:\n");
    FILE *arquivo = fopen("informations.bin","wb");   //Arquivo binario aberto para escrita
    information info;
    info.dado1 = 0;
    for (j = 0; j < 1000; j++) {
        info.dado2[j] = 'a'+ (char)(rand()%26);;   //preenchimento do information "dado2"
    }
    info.dado2[1000] = '\0';
    for (j = 0; j < 5000; j++) {
        info.dado3[j] = 'a'+ (char)(rand()%26);   //preenchimento do information "dado3"
    }
    info.dado3[5000] = '\0';
    switch(situacao) {
        case 1:
            for ( i = 1; i <= amount; i++) {  //A organiza��o dos dados � crescente  
                info.key = i;
                            dados.comparisons++;

                if (key)
                    printf("%d ", i);
                fwrite(&info, sizeof(information), 1, arquivo);
                dados.hits++;
            }
        break;
        case 2:
            for (i = amount; i >= 1; i--) {  //A organiza��o dos dados � decrescente 
                info.key = i;
                            dados.comparisons++;

                if (key) 
                    printf("%d ", i);
                fwrite(&info, sizeof(information), 1, arquivo);
                dados.hits++;
            }
        break;
        case 3:
            srand(time(NULL));
            char *score = malloc(sizeof(char) * amount + 1);
            for (i = 1; i <= amount; i++){
                score[i] = '0';
            }
            i=1;
            while(i <= amount){
                position = rand() % amount + 1;
                            dados.comparisons++;

                if(score[position] == '0') { 
                    score[position] = '1'; 
                    info.key = position; 
                    printf("%d ",position);
                    fwrite(&info, sizeof(information), 1, arquivo);
                    dados.hits++;
                    i++; 
                }
            }
            free(score);
        break;
        default:
            printf("\n Teste inexistente !\n");
        break;
    }

    time_end_ind = clock();

    //printf("\nkey : %d\n dado1 : %ld\n dado2 : %s\n dado3 : %s\n", info.key, info.dado1,info.dado2,info.dado3);
        printf("Numero de transferencias: %lld\n", dados.hits);
        printf("Numero de comparisons: %lld\n", dados.comparisons);
        dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
        printf("Tempo : %lfs\n",dados.time);

    fclose(arquivo);
}