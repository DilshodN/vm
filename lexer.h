#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#ifndef CEDU_LEXER_H
#define CEDU_LEXER_H

typedef enum {
    NUMBER = 0,
    INSTURCTION,
    REGISTER,
    FLAG,
    PARAN_OPEN,
    PARAN_CLOSE,
}
        LexemType;

typedef struct CharList {
    char val;
    struct CharList * next;
}
        CharList;

typedef struct {
    int id;
    LexemType type;
    char * name;

}
Lexem;

CharList * MakeCharList();
int Size(CharList * list);
void add(CharList * list, char c);
char Get(CharList * list, int n);
char * tostr(CharList * list);
void Print(CharList * list);
void Delete(CharList * list);
char * ReadFile(char * filename);
int isNumber(char * str);
int isRegister(char * str);
int isFlag(char * str);
int isOpenParan(char c);
int isCloseParan(char c);
void AddToken(Lexem * token);
Lexem * CreateToken(int id, LexemType type, char * name);
void Lex(char * text);
void print_token(Lexem * tok);
void PrintTokenList();
void DeleteToken(Lexem * tok);
void DeleteTokenList();
void CleanLexer();
Lexem * GetNextToken();
int get_numtokens();

#endif