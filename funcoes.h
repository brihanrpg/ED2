#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#ifndef funcoes_h
#define funcoes_h


typedef struct {
    int key;
    long int dado1;
    char dado2[1000];
    char dado3[5000];
}information;

typedef struct {
    long long int comparisons;
    long long int hits;
    double time;
} search;


search dados;

void create_file(int amount, int situation, int key);

#endif