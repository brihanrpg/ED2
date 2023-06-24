#include "funcoes.h"

# ifndef arvore_binaria_h
# define arvore_binaria_h

typedef struct {

    information data;
    int left;
    int right;
    
}Node;

void makeTree(int n);
void arvore_bin(int n, int key);

# endif