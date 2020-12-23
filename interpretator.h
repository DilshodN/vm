#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"
#define NUM_REGS 10
#ifndef CEDU_INTERPRETATOR_H
#define CEDU_INTERPRETATOR_H


void interpret();
void Ecall();
void print_registers_inline();
void print_mem(int n);


#endif
