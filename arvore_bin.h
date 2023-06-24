#include "funcoes.h"

# ifndef arvore_bin_h
# define arvore_bin_h
typedef struct {

    information data;
    int left;
    int right;
    
}Node;

int makeTree(int n);
void searchTree(int key, int n, char *nameArqTree);
void printData(information data);

# endif