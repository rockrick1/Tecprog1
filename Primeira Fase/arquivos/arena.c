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
axial move(axial a, int dir) {
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
	return cube_to_axial(c);
}

void destroiArena(Celula **arena, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(arena[i]);
    free(arena);
}