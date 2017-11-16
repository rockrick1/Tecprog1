/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

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
	"PRN",
	"ATR",
	"STS"
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
	m->hp = 10; /*cada avaria tira 1 de vida*/
	m->no = 0; /*nivel de ocupação*/
	m->ip = 0;
	m->bp = 0;
	m->prog = p;
	return m;
}

/**********************************************/
/* Retorna o tipo em string para impressão */
const char *getTipo(Tipo tipo) {
	switch (tipo) {
		case NUM: return "NUM";
		case ACAO: return "ACAO";
		case VAR: return "VAR";
		case CELULA: return "CELULA";
	}
}
/* Retorna o int correspondente de cada terreno */
const int getTerreno(Terreno terr) {
	switch (terr) {
		case ESTRADA: return 0;
		case MONTANHA: return 1;
		case RIO: return 2;
		case BASE: return 3;
	}
}
/**********************************************/

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
			OPERANDO op1;
			OPERANDO op2;
			OPERANDO res;

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
			/* A partir daqui, as funções foram adaptadas para a nova struct
			// do Operando, validando o seu tipo em cada uma delas */
			case ADD:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if (op1.t == NUM && op2.t == NUM) {
					res.t = NUM;
					res.val.n = op1.val.n + op2.val.n;
					empilha(pil, res);
				}
				break;
			case SUB:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if (op1.t == NUM && op2.t == NUM) {
					res.t = NUM;
					res.val.n = op1.val.n - op2.val.n;
					empilha(pil, res);
				}
				break;
			case MUL:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if (op1.t == NUM && op2.t == NUM) {
					res.t = NUM;
					res.val.n = op1.val.n * op2.val.n;
					empilha(pil, res);
				}
				break;
			case DIV:
				op1 = desempilha(pil);
				op2 = desempilha(pil);

				if (op1.t == NUM && op2.t == NUM) {
					res.t = NUM;
					res.val.n = op1.val.n / op2.val.n;
					empilha(pil, res);
				}
				break;
			case JMP:
				ip = arg.val.n;
				continue;
			case JIT:
				tmp = desempilha(pil);
				if (tmp.t == NUM && tmp.val.n != 0) {
					ip = arg.val.n;
					continue;
				}
				break;
			case JIF:
				tmp = desempilha(pil);
				if (tmp.t == NUM && tmp.val.n == 0) {
					ip = arg.val.n;
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
				op1.val.n = ip;
				op1.t = NUM;
				op2.val.n = bp;
				op2.t = NUM;

				empilha(exec, op1);
				empilha(exec, op2);

				bp = exec->topo - 1;
				ip = arg.val.n;
				continue;
			/* RET simplesmente desempilha também o bp que estava
			// sendo guardado */
			case RET:
				op1 = desempilha(exec);
				op2 = desempilha(exec);
				bp = op1.val.n;
				ip = op2.val.n;
				break;
			case EQ:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t == op2.t && op1.val.n == op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case GT:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t == op2.t && op1.val.n < op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case GE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t == op2.t && op1.val.n <= op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case LT:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t == op2.t && op1.val.n > op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case LE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t == op2.t && op1.val.n >= op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case NE:
				op1 = desempilha(pil);
				op2 = desempilha(pil);
				res.t = NUM;
				if (op1.t == NUM && op2.t == NUM) {
					if (op1.t != op2.t || op1.val.n != op2.val.n)
						res.val.n = 1;
					else
						res.val.n = 0;
					empilha(pil, res);
				}
				break;
			case STO:
				m->Mem[arg.val.n] = desempilha(pil);
				break;
			/* STL guarda o valor do topo da pilha de dados na
			// posição dada por bp atual + arg da pilha de execução
			// (precisa alocar o frame com ALC antes!) */
			case STL:
				exec->val[bp + arg.val.n] = desempilha(pil);
				break;
			case RCL:
				empilha(pil,m->Mem[arg.val.n]);
				break;
			/* RCE é basicamente o contrario do STL, ele guarda
			// a variavel loval de volta na pilha de dados, mas nao
			// tira ela da pilha de execução. Quem fará isso é o FRE */
			case RCE:
				empilha(pil, exec->val[bp + arg.val.n]);
				break;
			/* ALC serivrá para alocar um espaço extra na pilha de
			// execução, simplesmente alterando o topo */
			case ALC:
				exec->topo += arg.val.n;
				break;
			/* FRE naturalmente faz o contrario do ALC, subtraindo
			// do topo da pilha de execução */
			case FRE:
				exec->topo -= arg.val.n;
				break;
			case END:
				return;
			/* PRN utiliza uma função que interpreta o tipo do Operando para
			// imprimi-lo como string */
			case PRN:
				tmp = desempilha(pil);
				printf("[%s, %d]\n", getTipo(tmp.t), tmp.val.n);
				break;
			/* ATR desempilhará o operando e guardará o atributo definido por
			// arg, caso esse oprando seja um célula */
			case ATR:
				tmp = desempilha(pil);
				if (tmp.t == CELULA) {
					res.t = NUM;
					if (arg.val.n == 0) { /* Pediu o tipo de terreno */
						res.val.n = getTerreno(tmp.val.cell.terreno);
					}
					else if (arg.val.n == 1) { /* Pediu o numero de cristais */
						res.val.n = tmp.val.cell.cristais;
					}
					else if (arg.val.n == 2) { /* Pediu se está ocupado ou nao */
						res.val.n = tmp.val.cell.ocupado;
					}
					empilha(pil, res);
				}
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
