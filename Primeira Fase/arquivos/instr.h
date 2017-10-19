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
  VAR,
  CELULA
} Tipo;

/* Tipo de terreno */
typedef enum {
  ESTRADA,
  MONTANHA,
  RIO,
  BASE
} Terreno;

/* Célula */
typedef struct {
  Terreno terreno;
  short int cristais; /* numero de cristais presentes */
  short int ocupado; /* identificador do time se ocupado, -1 c.c */
} Celula;


/* Operando */
typedef struct {
  Tipo t;
  union {
	int n;
	int ac;
    int v;
	Celula cell;
  } val;
} OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
