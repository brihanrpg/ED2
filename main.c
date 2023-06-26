#include "funcoes.h"
#include "sequencial.h"
#include "arvore_binaria.h"
#include "arvore_b.h"
#include "arvore_b_est.h"

int main(int argc, char *argv[]) {
    dados.hits = dados.comparisons = 0;
    FILE *resultado_arquivo = fopen("resultado_pesquisa.txt", "w");
    if (resultado_arquivo == NULL) {
        printf("Erro ao abrir o arquivo de resultado.\n");
        return 1;
    }
    int key, n = 100, ordem = 1;
    
    srand(time(NULL));

    if(argc == 1){
        create_file(n,ordem, argc == 6);
        for(int j = 0; j <=10; j++){
        key = rand() % n;
        fprintf(resultado_arquivo, "Key = %d\n", key);
        fprintf(resultado_arquivo, "N = %d\n", n);

        printf("Pesquisa Sequencial:\n");
        sequential_access(n, key);
        fprintf(resultado_arquivo, "Pesquisa Sequencial:\n");
        fprintf(resultado_arquivo, "Hits: %lld\n", dados.hits);
        fprintf(resultado_arquivo, "Comparisons: %lld\n", dados.comparisons);
        fprintf(resultado_arquivo, "Tempo: %.6lf segundos\n\n", dados.time);
            dados.hits = 0;
        dados.comparisons = 0;
        printf("Pesquisa Binária:\n");
        arvore_bin(n, key);
        fprintf(resultado_arquivo, "Pesquisa Binária:\n");
        fprintf(resultado_arquivo, "Hits: %lld\n", dados.hits);
        fprintf(resultado_arquivo, "Comparisons: %lld\n", dados.comparisons);
        fprintf(resultado_arquivo, "Tempo: %.6lf segundos\n\n", dados.time);
            dados.hits = 0;
    dados.comparisons = 0;
        printf("Árvore B:\n");
        tree_b(n, key);
        fprintf(resultado_arquivo, "Árvore B:\n");
        fprintf(resultado_arquivo, "Hits: %lld\n", dados.hits);
        fprintf(resultado_arquivo, "Comparisons: %lld\n", dados.comparisons);
        fprintf(resultado_arquivo, "Tempo: %.6lf segundos\n\n", dados.time);
            dados.hits = 0;
    dados.comparisons = 0;
        printf("Árvore B*:\n");
        tree_b_star(n, key);
        fprintf(resultado_arquivo, "Árvore B*:\n");
        fprintf(resultado_arquivo, "Hits: %lld\n", dados.hits);
        fprintf(resultado_arquivo, "Comparisons: %lld\n", dados.comparisons);
        fprintf(resultado_arquivo, "Tempo: %.6lf segundos\n\n", dados.time);    
            dados.hits = 0;
    dados.comparisons = 0;
        }
    }
    else{
        create_file(atoi(argv[2]), atoi(argv[3]), (argc == 6));

            dados.hits = dados.comparisons = 0;


        switch(atoi(argv[1])){
            case 1:
        
               sequential_access(atoi(argv[2]), atoi(argv[4]));
            break;
            case 2:
                arvore_bin(atoi(argv[2]), atoi(argv[4]));
            break;
            case 3:
                tree_b(atoi(argv[2]), atoi(argv[4]));
            break;
            case 4:
                tree_b_star(atoi(argv[2]), atoi(argv[4]));
            break;
            default:
                printf("Metodo nao identificado!\n");
        }
    }
    
    fclose(resultado_arquivo);
    return 0;
}