#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

Celula **criaArena(int m, int n) {
    int i;
    Celula **arena = malloc(m * sizeof(Celula*));

    for (i = 0; i < m; i++)
        arena[i] = malloc(n * sizeof(Celula));
    return arena;
}

void destroiArena(Celula **arena, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(arena[i]);
    free(arena);
}