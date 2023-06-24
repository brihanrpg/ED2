#include "funcoes.h"

# ifndef sequencial_h
# define sequencial_h

typedef struct {
    int position;
    int key;
}tipoindice;

void ordenacao(int n);
void sequential_access(int n, int key);
# endif