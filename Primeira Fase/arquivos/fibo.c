#include <stdio.h>
#include "fibo.h"

// Coleta um cristal
INSTR robo[] = {
	{PUSH, {DIRECAO, 3}},
	{STS,  {ACAO, 0}}, // move
	{PUSH, {DIRECAO, 2}},
	{STS,  {ACAO, 1}}, // recolhe
	{PUSH, {DIRECAO, 2}},
	{STS,  {ACAO, 0}}, // move
	{PUSH, {DIRECAO, 1}},
	{STS,  {ACAO, 0}}, // move
	{PUSH, {DIRECAO, 1}},
	{STS,  {ACAO, 2}}, // deposita
	{END,  {NUM, 0}}
};

// Anda por cima de um cristal
// INSTR robo[] = {
// 	{PUSH, {DIRECAO, 3}},
// 	{STS,  {ACAO, 0}}, // move
// 	{PUSH, {DIRECAO, 2}},
// 	{STS,  {ACAO, 0}}, // move
// 	{PUSH, {DIRECAO, 2}},
// 	{STS,  {ACAO, 0}}, // move
// 	{PUSH, {DIRECAO, 1}},
// 	{STS,  {ACAO, 0}}, // move
// 	{PUSH, {DIRECAO, 1}},
// 	{STS,  {ACAO, 2}}, // deposita
// 	{END,  {NUM, 0}}
// };