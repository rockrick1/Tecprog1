#include <stdio.h>
#include "maq.h"


INSTR fat[] = {
    {PUSH, 5},  // 0
    {CALL, 4},  // 1
    {PRN,  0},  // 2
    {END,  0},  // 3

    // FAT
    {ALC,  1},  // 4
    {DUP,  0},  // 5
    {STL,  1},  // 6 n
    {PUSH, 1},  // 7
    {EQ,   0},  // 8 n == 1 ?
    {JIF, 13},  // 9
    {PUSH, 1},  // 10
    {FRE,  1},  // 11
    {RET,  0},  // 12
    {RCE,  1},  // 13 n
    {PUSH, 1},  // 14
    {SUB,  0},  // 15 n-1
    {CALL, 4},  // 16 fat(n-1)
    {RCE,  1},  // 17 n
    {MUL,  0},  // 18 n * fat(n-1)
    {FRE,  1},  // 19
    {RET,  0}   // 20
};

INSTR fibo[] = {
  {PUSH, 1},
  {DUP, 0},
  {STO, 0},
  {STO, 1},
  {PUSH, 10},
  {STO, 2},
  {RCL, 0},
  {RCL, 1},
  {DUP, 0},
  {STO, 0},
  {ADD, 0},
  {DUP, 0},
  {STO, 1},
  {PRN, 0},
  {RCL, 2},
  {PUSH, 1},
  {SUB, 0},
  {DUP, 0},
  {STO, 2},
  {PUSH, 0},
  {EQ, 0},
  {JIF, 6},
  {END, 0},
};


int main(int ac, char **av) {
    Maquina *maq = cria_maquina(fat);
    exec_maquina(maq, 100000);
    destroi_maquina(maq);
    return 0;
}