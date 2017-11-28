/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"


FILE *display;
int exer;

Arena *criaArena(int m, int n) {
    int i, j;
    Arena *arena = (Arena*)malloc(sizeof(Arena));

    exer = 0;

    arena->m = m;
    arena->n = n;
    arena->tempo = 0;
    arena->mapa = malloc(m * sizeof(Celula*));
    arena->ativos = malloc(MAX_EXERCITOS * sizeof(int));

    for (i = 0; i < MAX_EXERCITOS; i++)
        arena->ativos[i] = -1;

    for (i = 0; i < m; i++)
        arena->mapa[i] = malloc(n * sizeof(Celula));

    iniciaArena(arena);
    // display = popen("./apres", "w");
    return arena;
}


/*com a parte grafica, a img que vem como parametro é a imagem da base
void base(char img, int i, int j, Arena *arena){
    arena->mapa[i][j].terreno = BASE;
    arena->mapa[i][j].cristais = 0;

}*/

/* função que o gubi pediu, com mais um parametro que é o arena */
void cristais(Arena *arena, int n, int i, int j){
    arena->mapa[i][j].cristais = n;
}

void iniciaArena(Arena *arena) {
    /*coloca terrenos nas celulas com 50% de se estrada, 25% montanha e 25% rio
    // em teoria as bases são inseridas depois, por isso não verifica se é base*/
    int x,y;
    int i,j;
    x = arena->m;
    y = arena->n;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            /*inicia com 0 cristais*/
            arena->mapa[i][j].cristais = 0;
            arena->mapa[i][j].ocupado = -1;

             /*definição dos terrenos*/
            int a = rand() % 4;
            if (a == 0 || a == 1) {
                arena->mapa[i][j].terreno = ESTRADA;
            }
            else if (a == 2) {
                arena->mapa[i][j].terreno = MONTANHA;
            }
            else { /* a == 3 */
                arena->mapa[i][j].terreno = RIO;
            }
        }

        /*define cristais*/
        int b = rand() % 2;
        if (b == 1) {
            /*50% de ter 1*/
            cristais(arena, 1, i, j);

            b = rand() % 2;
            if (b == 1) {
                /* dentre esses 50% de ter 2*/
                cristais(arena, 2, i, j);
                b = rand() % 2;
                if (b == 1) {
                    /*dentre esses 50% de ter 3*/
                    cristais(arena, 3, i, j);
                }
            }
        }
    }
}

/*********************** FUNÇÕES DE MOVIMENTO ************************/

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
    /* Converte a coordenada quadrada para cubica,
    // para fazer as alterações */
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
    /* Se sair do mapa, não anda.
    // Devolve a coordenada convertida de volta para quadrada */
    axial temp = cube_to_axial(c);
    if (temp.r < 0 || temp.q < 0 || temp.r >= m || temp.q >= n) {
        return a;
    }

    return temp;
}

/*********************************************************************/


void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y) {
    int i;
    axial base, temp;
    base.r = y;
    base.q = x;
    int rob;
    rob=0;
    /* Insere o exercito no vetor de ativos.
    // i é a primeira posição de ativos com -1 */
    for (i = 0; arena->ativos[i] != -1; i++) {
        arena->ativos[i] = exercito;
    }

    /* Insere a Base no mapa */

    //base(img, x, y,arena);
    /*falta a imagem, mas pra isso é necessário a parte grafica*/

    arena->mapa[x][y].terreno = BASE;
    arena->mapa[x][y].cristais = 0;
    arena->mapa[x][y].ocupado = exercito;/*
    if (exer == 0) {
        fprintf(display, "rob baseA.png\n");
        fflush(display);
        fprintf(display, "%d %d %d %d %d\n", rob, -1, -1, x, y);
        fflush(display);
        rob++;
    }
    else {
        fprintf(display, "rob baseB.png\n");
        fflush(display);
        fprintf(display, "%d %d %d %d %d\n", rob+6, -1, -1, x, y);
        fflush(display);
        rob++;
    }*/
    /* Insere 6 robôs ao redor dela e registra
    // eles na matriz de maquinas */
    for (i = 0; i < 6; i++) {
        temp = move(arena, base, i);
        // printf("temp: %d,%d\n", temp.q, temp.r);
        // r = y e q = x
        arena->mapa[temp.r][temp.q].ocupado = exercito;
        /*
        if (exer == 0) {
            fprintf(display, "rob GILEAD_A.png\n");
            fflush(display);
            fprintf(display, "%d %d %d %d %d\n", rob, -1, -1, temp.r, temp.q);
            fflush(display);
            rob++;
        }
        else {
            fprintf(display, "rob GILEAD_B.png\n");
            fflush(display);
            fprintf(display, "%d %d %d %d %d\n", (rob + 6), -1, -1, temp.r, temp.q);
            fflush(display);
            rob++;
        }*/
    }
    exer++;

}

void removeExercito(Arena *arena, int exercito) {
    int i, j;
    /* Remove todos os robos desse exercito do mapa */
    for (i = 0; i < arena->m; i++) {
        for (j = 0; j < arena->n; j++) {
            if (arena->mapa[i][j].ocupado == exercito) {
                arena->mapa[i][j].ocupado = -1;
            }
        }
    }
    /* Remove esse exercito do vetor de exercitos ativos.
    // i é a posição do exercito no vetor de exercitos ativos */
    for (i = 0; arena->ativos[i] != exercito; i++) {
        arena->ativos[i] = -1;
    }
}

void printArena(Arena *arena) {
    int m = arena->m, n = arena->n;
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (arena->mapa[i][j].ocupado == -1)
                printf("%2c", '-');
            else
                printf("%2d", arena->mapa[i][j].ocupado);
        }
        printf("\n");
        for (int k = 0; k <= i; k++)
            printf(" ");
    }
}

void destroiArena(Arena *arena) {
    int i, j;
    for (i = 0; i < arena->m; i++)
        free(arena->mapa[i]);
    free(arena->mapa);
    free(arena->ativos);
    free(arena);
}
