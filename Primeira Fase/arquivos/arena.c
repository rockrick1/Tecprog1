#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

Arena *criaArena(int m, int n) {
    int i, j;
    Arena *arena = (Arena*)malloc(sizeof(Arena));
    arena->mapa = malloc(m * sizeof(Celula*));
    arena->ativos = malloc(MAX_EXERCITOS * sizeof(int));

    for (i = 0; i < MAX_EXERCITOS; i++) {
        arena->ativos[i] = -1;
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
axial move(axial a, int dir, int m, int n) {
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
    /* Se sair do mapa, não anda */
    axial temp = cube_to_axial(c);
    if (c.x < 0 || c.y < 0 || c.z < 0 || temp.r >= m || temp.q >= n)
        return a;
	return temp;
}


void insereExercito(Arena *arena, int exercito, int m, int n) {
    int i;
    axial base, temp;
    base.r = m;
    base.q = n;

    /* Insere o exercito no vetor de ativos.
    // i é a primeira posição de ativos com -1 */
    for (i = 0; arena->ativos[i] != -1; i++);
    arena->ativos[i] = exercito;

    /* Insere a Base no mapa */
    arena->mapa[m][n].terreno = BASE;

    /* Insere 6 robôs ao redor dela e registra
    // eles na matriz de robos */
    for (i = 0; i < 6; i++) {
        temp = move(base, i, m, n);
        arena->mapa[temp.r][temp.q].ocupado = exercito;
    }
}

void removeExercito(Arena *arena, int exercito, int m, int n) {
    int i, j;
    /* Remove todos os robôs desse exercito da arena */
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (arena->mapa[i][j].ocupado == exercito)
                arena->mapa[i][j].ocupado = -1;
    /* Removce esse exercito do vetor de exercitos ativos.
    // i é a posição do exercito no vetor de exercitos ativos */
    for (i = 0; arena->ativos[i] != exercito; i++);
    arena->ativos[i] = -1;
}

void destroiArena(Arena *arena, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(arena->mapa[i]);
    free(arena->mapa);
    free(arena->ativos);
    free(arena);
}