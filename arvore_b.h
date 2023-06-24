#include "funcoes.h"

#ifndef arvore_b_h
#define arvore_b_h

#define M 2

typedef struct Pagina* Nodo;

typedef struct Pagina {
    short n;
    information r[M + M];
    Nodo filhos[M + M + 1];
} Pagina;

void tree_b(int amount, int key);
void inicializa(Nodo *arv);
void release_tree_b(Nodo *no);
void insere(information reg, Nodo *ap);
int b_tree_search(information *x, Nodo ap);
void ins(information reg, Nodo ap, short *cresceu, information *reg_retorno, Nodo *ap_retorno);

#endif