#include "funcoes.h"
#include <math.h>
#ifndef arvore_b_est_h
#define arvore_b_est_h

#define M 2



typedef struct Pag* Nodo2;

typedef enum {
    Interna, Externa
} TipoIntExt;

typedef struct Pag {
    TipoIntExt pt;
    union{
        struct{
            int ni;
            int keys[M + M];
            Nodo2 sons[M + M + 1];
        }In; // interno
        struct{
            int ne;
            information r[M + M];
        }Ex; // externo
    } UU;
} Pag;


void initialize_b_star_tree(Nodo2 *tree);
void release_tree_b_star(Nodo2 *no);
int b_star_tree_search(information *x, Nodo2 *ap);
void insert_star(information reg, Nodo2 *ap);
void tree_b_star(int amount, int key);
void ins_est(information reg, Nodo2 ap, int *cresceu, int *reg_retorno, Nodo2 *ap_retorno);
//void create_file(int amount, int situation, int key);
void insert_external_page(Nodo2 ap, information reg);
void insert_internal_page(Nodo2 ap, int key, Nodo2 apDir);
#endif