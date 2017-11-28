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
INSTR *p;


void inicia() {
    maquinas = malloc(MAX_EXERCITOS*sizeof(Maquina**));
    for (int i = 0; i < MAX_EXERCITOS; i++)
        maquinas[i] = malloc(MAX_ROBOS*sizeof(Maquina*));
}


/* Atualiza a arena em um timestep. Instr é o numero de instruções que
// cada maquina rodará */
void atualiza(int instr) {
    /* Roda todas as maquinas de um exercito por vez, depois vai pra outro
    // exercito */
    for (int i = 0; i < MAX_EXERCITOS; i++) {
        for (int j = 0; maquinas[i][j] != NULL; j++) {
            /* se o nivel de ocupação for maior que 0, não executa a instrução
            // e no--.
            // Alem disso, o exercito precisa estar ativo */
            if (arena->ativos[i]) {
                if (maquinas[i][j]->no <= 0) {
                    exec_maquina(maquinas[i][j], instr, arena);
                }
                else {
                    maquinas[i][j]->no--;
                }
            }
        }
    }
    arena->tempo++;
}


void destroiTudo() {
    int i, j;
    for (i = 0; i < MAX_EXERCITOS; i++) {
        for (int j = 0; maquinas[i][j] != NULL; j++) {
            destroi_maquina(maquinas[i][j]);
        }
        free(maquinas[i]);
    }
    free(maquinas);
    destroiArena(arena);
}


/* Essa função é analogas à de inserir exercitos, mas
// alem de executá-la, elaa também atualiza a matriz de maquinas */
void insereRobos(int exercito, int x, int  y) {
    int i;
    axial base, temp;
    base.q = x;
    base.r = y;
    /* Atualiza o mapa */
    insereExercito(arena, p, exercito, x, y);

    for (i = 0; i < 6; i++) {
        temp = move(arena, base, i);
        // r = y e q = x
        maquinas[exercito][i] = cria_maquina(p, temp.q, temp.r, exercito);
    }
}
/***************************************************************************/


int main() {
    srand(time(NULL));
    inicia();

    /* NAO USAR VALOR IMPAR NA SEGUNDA COORDENADA DE TAMANHO (WTF) */
    arena = criaArena(12, 12);

    insereRobos(1, 2, 2);
    insereRobos(2, 5, 5);
    printArena(arena);
    removeExercito(arena, 2);
    // atualiza(10);
    printArena(arena);
    destroiTudo();
    return 0;
}

