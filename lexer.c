#include "lexer.h"


CharList * MakeCharList() {
    CharList * c = (CharList * ) malloc(sizeof(CharList));
    if (c == NULL) {
        printf("memory_error");
        exit(1);
    }
    c -> next = NULL;
    return c;
}

int Size(CharList * list) {
    if (list -> next == NULL) {
        return 0;
    } else {
        return Size(list -> next) + 1;
    }
}

void add(CharList * list, char c) {
    if (list -> next == NULL) {
        list -> next = MakeCharList();
        list -> val = c;

    } else {
        add(list -> next, c);
    }
}

char Get(CharList * list, int n) {
    if (n == 0) {
        return list -> val;
    } else {
        return Get(list -> next, n - 1);
    }
}

char * tostr(CharList * list) {
    int list_size = Size(list);
    char * str = malloc(sizeof(char) * list_size + 1);
    if (str == NULL) {
        printf("Memory Error in lib CHARLIST");
        exit(1);
    }

    int c;
    for (c = 0; c < list_size; c++) {
        str[c] = Get(list, c);
    }

    str[list_size] = '\0';

    return str;
}

void Print(CharList * list) {
    if (list -> next != NULL) {
        printf("%c", list -> val);
        Print(list -> next);
    }
}

void Delete(CharList * list) {
    if (list -> next == NULL)
        free(list);
    else {
        Delete(list -> next);
        free(list);
    }
}

char * ReadFile(char * filename) {
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "\"%s\" not available.\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);

    fseek(file, 0, SEEK_SET);

    size_t size = sizeof(char) * (length);

    char * contents = malloc(size + 1);
    if (contents == NULL) {
        fprintf(stderr, "Memory error\n");
        return 0;
    }
    fread(contents, size, 1, file);
    fclose(file);

    contents[size] = '\0';

    return contents;
}

int isNumber(char * str) {
    char first = str[0];

    if (isdigit(first) == 1)
        return 1;

    else if ((first == '-' || first == '+') && strlen(str) > 1) {
        for (int i = 1; i < strlen(str); i++) {
            if (!isdigit(str[i]))
                return 0;
        }
        return 1;
    } else
        return 0;
}

int isRegister(char * str) {
    char first = str[0];
    if (first == 'R' && strlen(str) == 2 && isdigit(str[1]))
        return 1;
    return 0;
}

int isFlag(char * str) {
    int first = str[0];
    if (first == '.' && str[strlen(str) - 1] == ':')
        return 1;
    return 0;
}

int isOpenParan(char c) {
    return c == '[';
}

int isCloseParan(char c) {
    return c == ']';
}

Lexem ** tokenList = NULL;
int numTokens = 0;
int currentToken = 0;

void AddToken(Lexem * token) {
    numTokens++;
    tokenList = realloc(tokenList, (numTokens) * sizeof(Lexem * ));
    if (tokenList == NULL) {
        printf("Memory Error in Lexer.AddToken");
        exit(1);
    }
    tokenList[numTokens - 1] = token;
}

Lexem * CreateToken(int id, LexemType type, char * name) {
    Lexem * token = (Lexem * ) malloc(sizeof(Lexem));
    if (token == NULL) {
        printf("memory_error");
        exit(1);
    }
    token -> id = id;
    token -> type = type;
    token -> name = name;
    return token;
}

void Lex(char * text) {
    size_t length = strlen(text);
    int read = 0;
    int id = 0;

    while (read < length) {
        char next = text[read];
        read++;
        if (isspace(next) || next == '\n' || next == '\t') {
            continue;
        } else if (isOpenParan(next) || isCloseParan(next)) {
            if (isOpenParan(next)) {
                AddToken(CreateToken(id, PARAN_OPEN, "["));
                id++;
            } else {
                AddToken(CreateToken(id, PARAN_CLOSE, "]"));
                id++;
            }
        } else {
            CharList * str_contents = MakeCharList();
            while (next != '\0' && next != ' ' && next != '\n') {
                if (isCloseParan(next)) {
                    read--;
                    break;
                }
                add(str_contents, next);
                next = text[read];
                read++;
            }

            char * string = tostr(str_contents);
            Delete(str_contents);
            if (isNumber(string)) {
                AddToken(CreateToken(id, NUMBER, string));
                id++;
            } else if (isRegister(string)) {
                AddToken(CreateToken(id, REGISTER, string));
                id++;
            } else if (isFlag(string)) {
                AddToken(CreateToken(id, FLAG, string));
                id++;
            } else {
                AddToken(CreateToken(id, INSTURCTION, string));
                id++;
            }
        }
    }
}

void print_token(Lexem * tok) {
    printf("id: %2d  Type: %2u  name:  %2s\n", tok -> id, tok -> type, tok -> name);
}

void PrintTokenList() {
    for (int i = 0; i < numTokens; i++) {
        Lexem * tok = tokenList[i];
        print_token(tok);
    }

}

void DeleteToken(Lexem * tok) {
    free(tok->name);
    free(tok);
}

void DeleteTokenList() {
    int t;
    for (t = 0; t < numTokens; t++) {
        DeleteToken(tokenList[t]);
    }

    free(tokenList);
    tokenList = NULL;
}

void CleanLexer() {
    DeleteTokenList();
    numTokens = 0;
    currentToken = 0;
}

Lexem * GetNextToken() {
    if (currentToken >= numTokens) {
        return NULL;
    } else {
        Lexem * next = tokenList[currentToken];
        currentToken++;
        return next;
    }
}

int get_numtokens() {
    return numTokens;
}
