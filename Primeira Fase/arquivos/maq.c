#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

// #define DEBUG

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "STL",
  "RCL",
  "RCE",
  "ALC",
  "FRE",
  "END",
  "PRN"
};
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->bp = 0;
  m->prog = p;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
/* Novo registrador de base,
// usado para definir os frames */
#define bp (m->bp)

#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n) {
  int i;

  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));

	switch (opc) {
	  OPERANDO tmp;
	case PUSH:
	  empilha(pil, arg);
	  break;
	case POP:
	  desempilha(pil);
	  break;
	case DUP:
	  tmp = desempilha(pil);
	  empilha(pil, tmp);
	  empilha(pil, tmp);
	  break;
	case ADD:
	  empilha(pil, desempilha(pil)+desempilha(pil));
	  break;
	case SUB:
	  tmp = desempilha(pil);
	  empilha(pil, desempilha(pil)-tmp);
	  break;
	case MUL:
	  empilha(pil, desempilha(pil)*desempilha(pil));
	  break;
	case DIV:
	  tmp = desempilha(pil);
	  empilha(pil, desempilha(pil)/tmp);
	  break;
	case JMP:
	  ip = arg;
	  continue;
	case JIT:
	  if (desempilha(pil) != 0) {
		ip = arg;
		continue;
	  }
	  break;
	case JIF:
	  if (desempilha(pil) == 0) {
		ip = arg;
		continue;
	  }
	  break;
	/***********************************************************
	* Decidimos não implementar as funções REST e SAVE pois
	* era possível alterar CALL e RET para fazer o trabalho
	* das duas primeiras, e consequentemente não ter que chamar
	* duas funções extrar em toda chamada de subrotina
	************************************************************/

	/* CALL agora salva o bp atual na pilha de execução
	// e atualiza-o com o valor do topo dela - 1, assim
	// o novo bp é a posição que o ultimo bp esta guardado */
	case CALL:
	  empilha(exec, ip);
      empilha(exec, bp);
      bp = exec->topo - 1;
	  ip = arg;
	  continue;
	/* RET simplesmente desempilha também o bp que estava
	// sendo guardado */
	case RET:
      bp = desempilha(exec);
      ip = desempilha(exec);
	  break;
	case EQ:
	  if (desempilha(pil) == desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case GT:
	  if (desempilha(pil) < desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case GE:
	  if (desempilha(pil) <= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LT:
	  if (desempilha(pil) > desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LE:
	  if (desempilha(pil) >= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case NE:
	  if (desempilha(pil) != desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case STO:
	  m->Mem[arg] = desempilha(pil);
	  break;
	/* STL guarda o valor do topo da pilha de dados na
	// posição dada por bp atual + arg da pilha de execução
	// (precisa alocar o frame com ALC antes!) */
    case STL:
      exec->val[bp + arg] = desempilha(pil);
      break;
	case RCL:
	  empilha(pil,m->Mem[arg]);
	  break;
	/* RCE é basicamente o contrario do STL, ele guarda
	// a variavel loval de volta na pilha de dados, mas nao
	// tira ela da pilha de execução. Quem fará isso é o FRE */
    case RCE:
      empilha(pil, exec->val[bp + arg]);
      break;
    /* ALC serivrá para alocar um espaço extra na pilha de
    // execução, simplesmente alterando o topo */
    case ALC:
      exec->topo += arg;
      break;
    /* FRE naturalmente faz o contrario do ALC, subtraindo
    // do topo da pilha de execução */
    case FRE:
      exec->topo -= arg;
      break;
	case END:
	  return;
	case PRN:
	  printf("%d\n", desempilha(pil));
	  break;
	}
    D(printf("pil: "));
	D(imprime(pil, 100));
    D(printf("\nexec: "));
    D(imprime(exec, 100));
	D(puts("\n"));

	ip++;
  }
}
