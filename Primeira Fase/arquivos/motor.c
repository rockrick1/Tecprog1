#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

Maquina ***maquinas; /* Vetor com todas as maquinas */
Arena *arena; /* Gloriosa arena */
INSTR *p; /* kill me */

void inicia() {
    maquinas = malloc(sizeof(Maquina**));
    for (int i = 0; i < MAX_EXERCITOS; i++) {
        maquinas[i] = malloc(MAX_ROBOS*sizeof(Maquina*));
        for (int j = 0; j < MAX_ROBOS; j++) {
            maquinas[i][j] = cria_maquina(p, -1, -1, i);
        }
    }
}

/* Atualiza a arena em um timestep. Instr é o numero de instruções que
// cada maquina rodará */
void atualiza(int instr) {
    int i, j;
    /* MAX_ROBOS e MAX_EXERCITOS temporarios */
    for (i = 0; i < MAX_ROBOS; i++) {
        for (j = 0; j < MAX_EXERCITOS; j++) {
            /* se o nivel de ocupação for maior que 0, não executa a instrução e no--, não sei se funfa */
            if (maquinas[j][i]->no <= 0) {
                exec_maquina(maquinas[j][i], instr, arena);
            }
            else {
                maquinas[j][i]->no -= 1;
            }
        }
    }
    arena->tempo++;
}

int main() {
    inicia();
    int i, j;
    for (i = 0; i < MAX_EXERCITOS*MAX_ROBOS; i++)
        for (int j = 0; j < MAX_ROBOS; j++)
            destroi_maquina(maquinas[i][j]);
    atualiza(10);

    return 0;
}

