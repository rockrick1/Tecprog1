/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fibo.h" /* Aqui temos o vetor de instruçoões dos robos  (nome fibo temporario)*/

Maquina ***maquinas; /* Matriz com todas as maquinas */
Arena *arena; /* Gloriosa arena */


void inicia() {
    maquinas = malloc(MAX_EXERCITOS*sizeof(Maquina**));
    for (int i = 0; i < MAX_EXERCITOS; i++) {
        maquinas[i] = malloc(MAX_ROBOS*sizeof(Maquina*));
        for (int j = 0; j < MAX_ROBOS; j++) {
            maquinas[i][j] = cria_maquina(robo, -1, -1, i); // i é o exercito
        }
    }
}


/* Atualiza a arena em um timestep. Instr é o numero de instruções que
// cada maquina rodará */
void atualiza(int instr) {
    /* Roda todas as maquinas de um exercito por vez, depois vai pra outro
    // exercito */
    for (int i = 0; i < MAX_EXERCITOS; i++) {
        /* Executa todas as maquinas vivas daquele exercito */
        for (int j = 0; maquinas[i][j]->vivo; j++) {
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
        for (int j = 0; j < MAX_ROBOS; j++) {
            destroi_maquina(maquinas[i][j]);
        }
        free(maquinas[i]);
    }
    free(maquinas);
    destroiArena(arena);
}


/* Essa função é analoga à de inserir exercitos, mas
// alem de executá-la, ela também atualiza a matriz de maquinas */
void insereRobos(int exercito, int x, int  y) {
    int j;
    axial base, temp;
    base.q = x;
    base.r = y;
    /* Atualiza o mapa */
    insereExercito(arena, robo, exercito, x, y);

    for (j = 0; j < 6; j++) {
        temp = move(arena, base, j, 0);
        /* Inicia a maquina */
        maquinas[exercito][j]->vivo = 1;
        maquinas[exercito][j]->xpos = temp.q;
        maquinas[exercito][j]->ypos = temp.r;
    }
}
/***************************************************************************/


int main() {
    // srand(time(NULL));
    inicia();

    arena = criaArena(15, 15);
    // arena->mapa[4][4].cristais = 1;

    insereRobos(0, 2, 2);
    insereRobos(1, 5, 5);
    printArena(arena);
    // for (int i = 0; i < 3; i++)
        // atualiza(15);
    exec_maquina(maquinas[0][3], 100, arena);
    printArena(arena);
    destroiTudo();
    return 0;
}

