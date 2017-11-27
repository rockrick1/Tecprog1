/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maq.h"

Maquina ***maquinas; /* Matriz com todas as maquinas */
Arena *arena; /* Gloriosa arena */
INSTR *p; /* kill me */

void inicia() {
    maquinas = malloc(sizeof(Maquina**));
    for (int i = 0; i < MAX_EXERCITOS; i++)
        maquinas[i] = malloc(MAX_ROBOS*sizeof(Maquina*));
}

/* Atualiza a arena em um timestep. Instr é o numero de instruções que
// cada maquina rodará */
void atualiza(int instr) {
    int i = 0, j = 0;
    /* MAX_ROBOS e MAX_EXERCITOS temporarios */
    while (maquinas[j][i] != NULL) {
        while (arena->ativos[j] != -1) {
            /* se o nivel de ocupação for maior que 0, não executa a instrução
            // e no-- */
            if (maquinas[j][i]->no <= 0) {
                exec_maquina(maquinas[j][i], instr, arena);
            }
            else {
                maquinas[j][i]->no--;
            }
        }
    }
    arena->tempo++;
}

void destroiTudo() {
    int i, j;
    for (i = 0; i < MAX_EXERCITOS; i++)
        for (int j = 0; j < MAX_ROBOS; j++)
            destroi_maquina(maquinas[i][j]);
}

void insereRobos(int exercito, int x, int  y) {
    int i;
    axial base, temp;
    base.q = x;
    base.r = y;
    insereExercito(arena, p, exercito, x, y);
    for (i = 0; i < 6; i++) {
        temp = move(arena, base, i);
        // r = y e q = x
        maquinas[exercito][i] = cria_maquina(p, temp.q, temp.r, exercito);
    }
}

int main() {
    srand(time(NULL));
    // inicia();
    arena = criaArena(10, 10);
    insereRobos(1, 2, 2);
    // atualiza(10);
    printArena(arena);
    // destroiTudo();
    return 0;
}

