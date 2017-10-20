#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

Arena *criaArena(int m, int n) {
    int i, j;
    Arena *arena = (Arena*)malloc(sizeof(Arena));

    arena->m = m;
    arena->n = n;
    arena->tempo = 0;
    arena->mapa = malloc(m * sizeof(Celula*));
    arena->ativos = malloc(MAX_EXERCITOS * sizeof(int));
    arena->maquinas = malloc(MAX_EXERCITOS * sizeof(Maquina*));

    for (i = 0; i < MAX_EXERCITOS; i++) {
        arena->ativos[i] = -1;
        arena->maquinas[i] = malloc(MAX_ROBOS * sizeof(Maquina));
    }

    for (i = 0; i < m; i++)
        arena->mapa[i] = malloc(n * sizeof(Celula));
    return arena;
}

axial cube_to_axial(cube c) {
	axial a;
	a.q = c.x;
	a.r = c.z;
	return a;
}

cube axial_to_cube(axial a) {
	cube c;
	c.x = a.q;
	c.z = a.r;
	c.y = -c.x-c.z;
	return c;
}

/* dir: 0
      5   1
      4   2
        3
*/
axial move(Arena *arena, axial a, int dir) {
    int m = arena->m;
    int n = arena->n;
	cube c = axial_to_cube(a);
	if (dir == 0) {
		c.y++;
		c.z--;
	}
	else if (dir == 1) {
		c.x++;
		c.z--;
	}
	else if (dir == 2) {
		c.x++;
		c.y--;
	}
	else if (dir == 3) {
		c.y--;
		c.z++;
	}
	else if (dir == 4) {
		c.x--;
		c.z++;
	}
	else { /* dir == 5 */
		c.x--;
		c.y++;
	}
    /* Se sair do mapa ou se a posição desejada
    // ja estiver ocupada, não anda */
    axial temp = cube_to_axial(c);
    if (temp.r < 0 || temp.q < 0 ||
        temp.r >= m || temp.q >= n ||
        arena->mapa[temp.r][temp.q].ocupado != -1)
        return a;
	return temp;
}

/* Executa um robo de cada exercito por vez */
void atualiza(Arena *arena, int instr) {
    int i, j;
    /* MAX_ROBOS e MAX_EXERCITOS sao temporarios */
    for (i = 0; i < MAX_ROBOS; i++) {
        for (j = 0; j < MAX_EXERCITOS; j++) {
            exec_maquina(arena->maquinas[j][i], instr);
        }
    }
}


void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y) {
    int i;
    axial base, temp;
    base.r = x;
    base.q = y;

    /* Insere o exercito no vetor de ativos.
    // i é a primeira posição de ativos com -1 */
    for (i = 0; arena->ativos[i] != -1; i++);
        arena->ativos[i] = exercito;

    /* Insere a Base no mapa */
    arena->mapa[x][y].terreno = BASE;

    /* Insere 6 robôs ao redor dela e registra
    // eles na matriz de maquinas */
    for (i = 0; i < 6; i++) {
        temp = move(arena, base, i);
        arena->mapa[temp.r][temp.q].ocupado = exercito;
        arena->maquinas[exercito][i] = cria_maquina(p);
    }
}

void removeExercito(Arena *arena, int exercito) {
    int i, j;
    /* Removce todos os robos desse exercito do mapa */
    for (i = 0; i < arena->m; i++)
        for (j = 0; j < arena->n; j++)
            if (arena->mapa[i][j].ocupado == exercito)
                arena->mapa[i][j].ocupado = -1;
    /* Removce esse exercito do vetor de exercitos ativos.
    // i é a posição do exercito no vetor de exercitos ativos */
    for (i = 0; arena->ativos[i] != exercito; i++);
    arena->ativos[i] = -1;
}

void destroiArena(Arena *arena, int m) {
    int i, j;
    for (i = 0; i < m; i++)
        free(arena->mapa[i]);
    for (i = 0; i < MAX_EXERCITOS; i++) {
        for (j = 0; j < MAX_ROBOS; j++) {
            destroi_maquina(arena->maquinas[i][j]);
        }
        free(arena->maquinas[i]);
    }
    free(arena->maquinas);
    free(arena->mapa);
    free(arena->ativos);
    free(arena);
}