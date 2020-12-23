#include "run.h"

void run(){
    char* read = ReadFile("/Users/dilshod/CLionProjects/cedu/factorial.diasm");
    CleanLexer();
    Lex(read);
    PrintTokenList();
    Parse();
    print_execlinelist();
    interpret();

    //frees
    free(read);
    CleanLexer();
    DeleteExecutableLine();
}