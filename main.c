#include "funcoes.h"
#include "sequencial.h"
#include "arvore_binaria.h"
#include "arvore_b.h"
#include "arvore_b_est.h"

int main(int argc, char *argv[]) {
    int key, n = 100, ordem = 3;

    srand(time(NULL));

    if (argc == 1) {
        for (int j = 1; j <= 4; j++) {
            key = rand() % n;
            printf("Key = %d\n", key);
            printf("N = %d\n", n);

            create_file(n, ordem, 0);

            printf("Pesquisa Sequencial:\n");
            sequential_access(n, key);

            printf("Pesquisa binaria:\n");
            arvore_bin(n, key);

            printf("Arvore B:\n");
            tree_b(n, key);

            printf("Arvore B*:\n");
            tree_b_star(n, key);

            n *= 10;
        }
    }
    else {
        create_file(atoi(argv[2]), atoi(argv[3]), (argc == 6));

        int method = atoi(argv[1]);
        switch (method) {
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

    return 0;
}
