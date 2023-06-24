#include "arvore_b.h"

// Função principal para a operação da árvore B
void tree_b(int amount, int key) {
    int i;
    information info;
    Nodo tree;
    info.key = key;
    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();
    inicializa(&tree);
    FILE* arquivo;
    if ((arquivo = fopen("informations.bin", "rb")) == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    information* aux = (information*)malloc(amount * sizeof(information));
    while (fread(aux, sizeof(information), amount, arquivo)) {
        dados.hits = amount;
        i = 0;
        while (i < amount) {
            insere(aux[i], &tree);
            i++;
        }
    }
    free(aux);
    time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparisons: %lld\n", dados.comparisons);
    printf("Tempo : %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    dados.hits = 0;
    dados.comparisons = 0;

    time_begin_ind = clock();
    fclose(arquivo);

    if (b_tree_search(&info, tree)) {
        printf("\nkey : %d\n dado1 : %ld\n dado2 : %s\n dado3 : %s\n", info.key, info.dado1, info.dado2, info.dado3);
        printf("Numero de transferencias: %lld\n", dados.hits);
        printf("Numero de comparisons: %lld\n", dados.comparisons);
        printf("Tempo : %lfs\n", (double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    }
    else {
        printf("key nao encontrada!\n");
    }

    release_tree_b(&tree);
}

// Função para inicializar a árvore B
void inicializa(Nodo* arv) {
    *arv = NULL;
}

// Função para liberar a memória ocupada pela árvore B
void release_tree_b(Nodo* no) {
    if (*no == NULL) return;
    for (int i = 0; i < (*no)->n; i++) {
        release_tree_b(&(*no)->filhos[i]);
        free((*no)->filhos[i]);
    }
}

// Função para buscar uma chave na árvore B
int b_tree_search(information* x, Nodo ap) {
    long i = 1;
    if (ap == NULL) return 0;
    while (i < ap->n && x->key > ap->r[i - 1].key) {
        i++;
        dados.comparisons++;
    }
    if (i < ap->n && !(x->key > ap->r[i - 1].key)) {
        dados.comparisons++;
    }
    dados.comparisons++;
    if (x->key == ap->r[i - 1].key) {
        *x = ap->r[i - 1];
        return 1;
    }
    dados.comparisons++;
    if (x->key < ap->r[i - 1].key)
        return b_tree_search(x, ap->filhos[i - 1]);
    else
        return b_tree_search(x, ap->filhos[i]);
}

// Função para inserir um registro na árvore B
void insere(information reg, Nodo* ap) {
    short cresceu;
    information reg_retorno;
    Nodo ap_retorno, ap_temp;
    ins(reg, *ap, &cresceu, &reg_retorno, &ap_retorno);
    dados.comparisons++;
    if (cresceu) {
        ap_temp = (Pagina*)malloc(sizeof(Pagina));
        ap_temp->n = 1;
        ap_temp->r[0] = reg_retorno;
        ap_temp->filhos[1] = ap_retorno;
        ap_temp->filhos[0] = *ap;
        *ap = ap_temp;
    }
}

// Função auxiliar para inserir um registro em uma página da árvore B
void insere_na_pagina(Nodo ap, information reg, Nodo apDir) {
    int k = ap->n;
    short nao_achou_posicao = (k > 0);
    while (nao_achou_posicao) {
        dados.comparisons++;
        if (reg.key >= ap->r[k - 1].key) {
            nao_achou_posicao = 0;
            break;
        }
        ap->r[k] = ap->r[k - 1];
        ap->filhos[k + 1] = ap->filhos[k];
        k--;
        dados.comparisons++;
        if (k < 1) nao_achou_posicao = 0;
    }
    ap->r[k] = reg;
    ap->filhos[k + 1] = apDir;
    ap->n++;
}

// Função recursiva para inserir um registro na árvore B
void ins(information reg, Nodo ap, short* cresceu, information* reg_retorno, Nodo* ap_retorno) {
    long i = 1;
    Nodo ap_temp;
    if (ap == NULL) {
        *cresceu = 1;
        (*reg_retorno) = reg;
        (*ap_retorno) = NULL;
        return;
    }
    while (i < ap->n && reg.key > ap->r[i - 1].key) {
        i++;
        dados.comparisons++;
    }
    dados.comparisons++;
    if (i < ap->n && !(reg.key > ap->r[i - 1].key)) {
        dados.comparisons++;
    }
    if (reg.key == ap->r[i - 1].key) {
        printf("information ja esta presente!\n");
        *cresceu = 0;
        return;
    }
    if (reg.key < ap->r[i - 1].key) {
        dados.comparisons++;
        i--;
    }
    else {
        dados.comparisons++;
    }

    ins(reg, ap->filhos[i], cresceu, reg_retorno, ap_retorno);
    dados.comparisons++;
    if (!(*cresceu)) return;
    dados.comparisons++;
    if (ap->n < M + M) {
        insere_na_pagina(ap, *reg_retorno, *ap_retorno);
        *cresceu = 0;
        return;
    }
    // A página precisa ser dividida
    ap_temp = (Nodo)malloc(sizeof(Pagina));
    ap_temp->n = 0;
    ap_temp->filhos[0] = NULL;
    dados.comparisons++;
    if (i < M + 1) {
        insere_na_pagina(ap_temp, ap->r[M + M - 1], ap->filhos[M + M]);
        ap->n--;
        insere_na_pagina(ap, *reg_retorno, *ap_retorno);
    }
    else {
        insere_na_pagina(ap_temp, *reg_retorno, *ap_retorno);
    }
    for (int j = M + 2; j <= M + M; j++)
        insere_na_pagina(ap_temp, ap->r[j - 1], ap->filhos[j]);
    ap->n = M;
    ap_temp->filhos[0] = ap->filhos[M + 1];
    *reg_retorno = ap->r[M];
    *ap_retorno = ap_temp;
}
