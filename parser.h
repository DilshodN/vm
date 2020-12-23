#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include "lexer.h"

#ifndef CEDU_PARSER_H
#define CEDU_PARSER_H

typedef enum {
    ADD,
    ADDI,
    SUB,
    NEG,
    DIV,
    REM,
    ECALL,
    BEQ,
    BNE,
    BLT,
    BGT,
    BLE,
    BGE,
    BEQZ,
    BNEZ,
    BGTZ,
    BLEZ,
    BGEZ,
    JUMP,
    LI,
    MV,
    MUL,
    FLAG_INST,
    ARTEM,
    SWI,
    LWI,
    ADDF,
    PRINT,
    PRINTMEM,
    CALL,
    RET
}
        INSTURCTIONS;

typedef struct {
    union {
        char * flag_name;
        int Register;
        int num;
        int flag_idx;
    };
}
        Argument;

typedef struct ListArguments {
    Argument arg;
    struct ListArguments * next;
}
        ListArguments;

typedef struct Instr {
    INSTURCTIONS insturction;
    ListArguments * args;

}
        Instr;

ListArguments * MakeArgsList();
int ListArgumentsSize(ListArguments * list);
void AddArg(ListArguments * list, Argument arg);
Argument GetArg(ListArguments * list, int n);
void DeleteArgs(ListArguments * list);
int num_reg(Lexem * lexem);
void AddInstr(Instr * function);
void Parse();
void print_execlinelist();
void print_instr(Instr * instr);
void print_arguments(Instr * instr);
void DeleteInstr(Instr * instruction);
void DeleteExecutableLine();
int getnumInstr();
Instr ** getExecLine();
int FindFlag(char * name);

#endif