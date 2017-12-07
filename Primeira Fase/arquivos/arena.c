/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"


FILE *display;
short int EXER; // Servirá para desenhar exercitos diferentes de forma diferente

Arena *criaArena(int m, int n) {
    int i;
    Arena *arena = malloc(sizeof(Arena));

    EXER = 0;

    arena->m = m;
    arena->n = n;
    arena->tempo = 0;
    arena->ativos = malloc(MAX_EXERCITOS * sizeof(int));

    for (i = 0; i < MAX_EXERCITOS; i++)
        arena->ativos[i] = 0;

    arena->mapa = malloc(m * sizeof(Celula*));
    for (i = 0; i < m; i++)
        arena->mapa[i] = malloc(n * sizeof(Celula));

    display = popen("./apres", "w");
    // display = fopen("./display", "w");
    iniciaArena(arena);
    return arena;
}


void insereBase(Arena *arena, int i, int j, int exercito) {
    arena->mapa[i][j].terreno = BASE;
    arena->mapa[i][j].cristais = 0;
    arena->mapa[i][j].ocupado = exercito;
}

/* Seta o numero de cristais em i j para n */
void insereCristais(Arena *arena, int n, int i, int j){
    fprintf(display, "cristal %d %d %d\n", n, i, j);
    arena->mapa[i][j].cristais = n;
}

void iniciaArena(Arena *arena) {
    /* coloca terrenos nas celulas com 50% de se estrada, 25% montanha e 25% rio
    // em teoria as bases são inseridas depois, por isso não verifica se é base*/
    int m, n;
    int i, j;
    m = arena->m;
    n = arena->n;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            /* inicia com 0 cristais */
            arena->mapa[i][j].cristais = 0;
            arena->mapa[i][j].ocupado = -1;

            /* definição dos terrenos */
            /* 40% estrada, 30% montanha, 20% rio e 10% lava */
            int a = rand() % 10;
            if (a <= 3) {
                arena->mapa[i][j].terreno = ESTRADA;
                fprintf(display, "terreno ESTRADA %d %d\n", i, j);
            }
            else if (a <= 6) {
                arena->mapa[i][j].terreno = MONTANHA;
                fprintf(display, "terreno MONTANHA %d %d\n", i, j);
            }
            else if (a < 9){
                arena->mapa[i][j].terreno = RIO;
                fprintf(display, "terreno RIO %d %d\n", i, j);
            }
            else if (a == 9){
                arena->mapa[i][j].terreno = LAVA;
                fprintf(display, "terreno LAVA %d %d\n", i, j);
            }

            /* define cristais */
            int b = rand() % 10;
            if (b == 1) {
                /* 10% de ter 1 */
                insereCristais(arena, 1, i, j);

                b = rand() % 2;
                if (b == 1) {
                    /* dentre esses 50% de ter 2 */
                    insereCristais(arena, 2, i, j);

                    b = rand() % 2;
                    if (b == 1) {
                        /* dentre esses 50% de ter 3 */
                        insereCristais(arena, 3, i, j);
                    }
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
axial move(Arena *arena, axial a, int dir, int mover) {
    int m = arena->m;
    int n = arena->n;
    /* Converte a coordenada quadrada para cubica para fazer as alterações */
    cube c = axial_to_cube(a);
    if (dir == 0) {
        c.x++;
        c.z--;
    }
    else if (dir == 1) {
        c.x++;
        c.y--;
    }
    else if (dir == 2) {
        c.y--;
        c.z++;
    }
    else if (dir == 3) {
        c.x--;
        c.z++;
    }
    else if (dir == 4) {
        c.x--;
        c.y++;
    }
    else { /* dir == 5 */
        c.y++;
        c.z--;
    }
    /* Se sair do mapa, não anda.
    // Devolve a coordenada convertida de volta para quadrada */
    axial temp = cube_to_axial(c);
    if (temp.r < 0 || temp.q < 0 || temp.r >= m || temp.q >= n) {
        return a;
    }
    /* Atualiza o display, caso o robo realmente estja sendo movido */
    if (mover) {
        fprintf(display, "move %d %d %d %d\n", a.q, a.r, temp.q, temp.r);
        int c = arena->mapa[a.r][a.q].cristais;
        /* Gambiarra monstra, desenha o cristal denovo se tiver um quando
        // um robo sair da celula */
        fprintf(display, "cristal %d %d %d\n", c, a.r, a.q);
    }

    return temp;
}

/*********************************************************************/


void insereExercito(Arena *arena, INSTR *p, int exercito, int x, int y) {
    int i;
    axial base, temp;
    base.r = y;
    base.q = x;

    /* "Ativa" o exercito no vetor de ativos */
    arena->ativos[exercito] = 1;

    /* Insere a base na arena */
    insereBase(arena, x, y, exercito);

    /* Desenha ela */
    if (EXER == 0) {
        fprintf(display, "base baseA.png\n");
        fprintf(display, "drawbase %d %d %d\n", exercito, x, y);
    }
    else {
        fprintf(display, "base baseB.png\n");
        fprintf(display, "drawbase %d %d %d\n", exercito, x, y);
    }

    /* Insere 6 robôs ao redor dela e desenha eles. O motor.c que
    // registrará elas na matriz de maquinas */
    for (i = 0; i < 6; i++) {
        temp = move(arena, base, i, 0);
        // r = y e q = x
        arena->mapa[temp.r][temp.q].ocupado = exercito;

        if (EXER == 0) {
            fprintf(display, "rob GILEAD_A.png %d %d\n", temp.q, temp.r);
        }
        else {
            fprintf(display, "rob GILEAD_B.png %d %d\n", temp.q, temp.r);
        }
    }
    fflush(display);
    EXER++;
}

void removeExercito(Arena *arena, int exercito) {
    /* Remove todos os robos desse exercito do mapa */
    for (int i = 0; i < arena->m; i++) {
        for (int j = 0; j < arena->n; j++) {
            if (arena->mapa[i][j].ocupado == exercito) {
                arena->mapa[i][j].ocupado = -1;
            }
        }
    }
    /* Remove esse exercito do vetor de exercitos ativos.
    // i é a posição do exercito no vetor de exercitos ativos */
    arena->ativos[exercito] = 0;
}

void printArena(Arena *arena) {
    int m = arena->m, n = arena->n;
    int i, j;
    for (i = 0; i < m; i++) {
        for (int k = 0; k < i; k++)
            printf(" ");
        for (j = 0; j < n; j++) {
            if (arena->mapa[i][j].terreno == BASE)
                printf("%2c", 'B');
            else if (arena->mapa[i][j].cristais > 0)
                printf("%2c", 'c');
            else if (arena->mapa[i][j].ocupado == -1)
                printf("%2c", '-');
            else
                printf("%2d", arena->mapa[i][j].ocupado);
        }
        printf("\n");
    }
}

void destroiArena(Arena *arena) {
    pclose(display);
    // fclose(display);
    int i;
    for (i = 0; i < arena->m; i++) {
        free(arena->mapa[i]);
    }
    free(arena->mapa);
    free(arena->ativos);
    free(arena);
}
