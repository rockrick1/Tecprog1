/*//////////////////////////////////////////////////////////////////////
// Nome: Leonardo Ikeda                                 NUSP: 10262822//
// Nome: Henrique Cerquinho                             NUSP: 9793700///
// Nome: Henrique Suzuki                                NUSP: 10297626//
//////////////////////////////////////////////////////////////////////*/

/* Códigos das instruções */
typedef enum {
  PUSH,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  STL,
  RCL,
  RCE,
  ALC,
  FRE,
  END,
  PRN,
  ATR,
  STS
} OpCode;

/* Tipos dos operandos */
typedef enum {
  NUM,
  ACAO,
  DIRECAO,
  CELULA
} Tipo;

/* Tipo de terreno */
typedef enum {
  ESTRADA,
  MONTANHA,
  RIO,
  LAVA,
  BASE
} Terreno;

/* Célula */
typedef struct {
  Terreno terreno; /* tipo de terreno dessa celula */
  short int cristais; /* numero de cristais presentes */
  short int ocupado; /* identificador do time se ocupado, -1 c.c */
} Celula;

/* Novo operando, com dois campos, uma para o tipo e outro para o
// valor do tipo em questão */
typedef struct {
  Tipo t;
  union {
	int n;
	int ac;
    int dir;
	Celula cell;
  } val;
} OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
