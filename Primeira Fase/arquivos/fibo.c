#include <stdio.h>
#include "fibo.h"


INSTR robo[] = {
	{PUSH, {DIRECAO, 3}},
	{STS,  {ACAO, 0}},
	{PUSH, {DIRECAO, 2}},
	{STS,  {ACAO, 0}},
	{PUSH, {DIRECAO, 2}},
	{STS,  {ACAO, 1}}, // recolhe
	{PUSH, {DIRECAO, 3}},
	{STS,  {ACAO, 0}},
	{PUSH, {DIRECAO, 4}},
	{STS,  {ACAO, 0}},
	{PUSH, {DIRECAO, 4}},
	{STS,  {ACAO, 2}}, // deposita
	{END,  {NUM, 0}}
};