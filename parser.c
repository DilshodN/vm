#include "parser.h"

ListArguments * MakeArgsList() {
    ListArguments * args = (ListArguments * ) malloc(sizeof(ListArguments));
    if (args == NULL) exit(1);
    args -> next = NULL;
    return args;
}

int ListArgumentsSize(ListArguments * list) {
    if (list -> next == NULL) {
        return 0;
    } else {
        return ListArgumentsSize(list -> next) + 1;
    }
}

void AddArg(ListArguments * list, Argument arg) {
    if (list -> next == NULL) {
        list -> next = MakeArgsList();
        list -> arg = arg;

    } else {
        AddArg(list -> next, arg);
    }
}

Argument GetArg(ListArguments * list, int n) {
    if (n == 0) {
        return list -> arg;
    } else {
        return GetArg(list -> next, n - 1);
    }
}

void DeleteArgs(ListArguments * list) {
    if (list -> next == NULL)
        free(list);
    else {
        DeleteArgs(list -> next);
        free(list);
    }
}

Instr * create_f(INSTURCTIONS type) {
    Instr * newFunc = (Instr * ) malloc(sizeof(Instr));
    if (newFunc == NULL) exit(1);
    newFunc -> insturction = type;
    newFunc -> args = MakeArgsList();
    return newFunc;
}

int num_reg(Lexem * lexem) {
    if (!strcmp(lexem -> name, "R0"))
        return 0;
    else if (!strcmp(lexem -> name, "R1"))
        return 1;
    else if (!strcmp(lexem -> name, "R2"))
        return 2;
    else if (!strcmp(lexem -> name, "R3"))
        return 3;
    else if (!strcmp(lexem -> name, "R4"))
        return 4;
    else if (!strcmp(lexem -> name, "R5"))
        return 5;
    else if (!strcmp(lexem -> name, "R6"))
        return 6;
    else if (!strcmp(lexem -> name, "R7"))
        return 7;
    else if (!strcmp(lexem -> name, "R8"))
        return 8;
    else if (!strcmp(lexem -> name, "R9"))
        return 9;
    return -1;
}

Instr ** ExecutableLine = NULL;
int numInstr = 0;

void AddInstr(Instr * function) {
    numInstr++;
    ExecutableLine = realloc(ExecutableLine, (numInstr) * sizeof(Instr * ));
    if (ExecutableLine == NULL) {
        printf("Memory Error in ExecLine");
        exit(1);
    }
    ExecutableLine[numInstr - 1] = function;
}

void print_arguments(Instr * instr) {
    for (int j = 0; j < ListArgumentsSize(instr -> args); j++) {
        int argument = GetArg(instr -> args, j).Register;
        printf("Argument:%d \n", argument);
    }
    printf("-------------------------\n");

}

void print_instr(Instr * instr) {
    printf("Type: %u\n", instr -> insturction);
    print_arguments(instr);
}

void print_execlinelist() {
    for (int i = 0; i < numInstr; i++) {
        Instr * inst = ExecutableLine[i];
        print_instr(inst);
    }
}

void DeleteInstr(Instr * instruction) {
    DeleteArgs(instruction -> args);
    free(instruction);
}

void DeleteExecutableLine() {
    int t;
    for (t = 0; t < numInstr; t++) {
        DeleteInstr(ExecutableLine[t]);
    }

    free(ExecutableLine);
    ExecutableLine = NULL;
}

int getnumInstr() {
    return numInstr;
}

Instr ** getExecLine() {
    return ExecutableLine;
}

// Это не оптимально...
int FindFlag(char * name) {
    for (int i = 0; i < numInstr; i++) {
        if (ExecutableLine[i] -> insturction == FLAG_INST) {
            if (!strcmp(ExecutableLine[i] -> args -> arg.flag_name, name)) {
                return i;
            }
        }
    }
    return -1;
}

void Parse() {
    for (int i = 0; i < get_numtokens(); i++) {
        Lexem * lexem = GetNextToken();
        switch (lexem -> type) {
            case FLAG: {
                Instr * f = create_f(FLAG_INST);
                Argument arg;
                arg.flag_name = lexem -> name;
                AddArg(f -> args, arg);
                AddInstr(f);
                break;
            }
            case INSTURCTION:
                if (!strcmp(lexem -> name, "ADD")) {
                    Instr * f = create_f(ADD);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "ADDI")) {
                    Instr * f = create_f(ADDI);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg;
                    arg.num = atoi(lexem_arg -> name);
                    AddArg(f -> args, arg);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "SUB")) {
                    Instr * f = create_f(SUB);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "NEG")) {
                    Instr * f = create_f(NEG);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "DIV")) {
                    Instr * f = create_f(DIV);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "REM")) {
                    Instr * f = create_f(REM);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "ECALL")) {
                    Instr * f = create_f(ECALL);
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "BEQ")) {
                    Instr * f = create_f(BEQ);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);

                }
                if (!strcmp(lexem -> name, "BNE")) {
                    Instr * f = create_f(BNE);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BLT")) {
                    Instr * f = create_f(BLT);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BGT")) {
                    Instr * f = create_f(BGT);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BLE")) {
                    Instr * f = create_f(BLE);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BGE")) {
                    Instr * f = create_f(BGE);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BEQZ")) {
                    Instr * f = create_f(BEQZ);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg);
                    AddArg(f -> args, reg);

                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BNEZ")) {
                    Instr * f = create_f(BNEZ);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg);
                    AddArg(f -> args, reg);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BGTZ")) {
                    Instr * f = create_f(BGTZ);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg);
                    AddArg(f -> args, reg);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BLEZ")) {
                    Instr * f = create_f(BLEZ);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg);
                    AddArg(f -> args, reg);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "BGEZ")) {
                    Instr * f = create_f(BGEZ);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg);
                    AddArg(f -> args, reg);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "JUMP")) {
                    Instr * f = create_f(JUMP);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "LI")) {
                    Instr * f = create_f(LI);

                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument reg;
                    reg.Register = num_reg(lexem_arg1);
                    AddArg(f -> args, reg);

                    Lexem * lexem_arg2 = GetNextToken();
                    i++;
                    Argument num;
                    num.num = atoi(lexem_arg2 -> name);
                    AddArg(f -> args, num);

                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "MV")) {
                    Instr * f = create_f(MV);
                    for (int j = 0; j < 2; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "MUL")) {
                    Instr * f = create_f(MUL);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "ARTEM")) {
                    Instr * f = create_f(ARTEM);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "SWI")) {
                    Instr * f = create_f(SWI);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument reg1;
                    reg1.Register = num_reg(lexem_arg1);
                    AddArg(f -> args, reg1);

                    Lexem * lexem_arg2 = GetNextToken();
                    i++;
                    Argument imm;
                    imm.num = atoi(lexem_arg2 -> name);
                    AddArg(f -> args, imm);

                    Lexem * lexem_arg3 = GetNextToken();
                    i++;
                    Argument reg2;
                    reg2.Register = num_reg(lexem_arg3);
                    AddArg(f -> args, reg2);

                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "LWI")) {
                    Instr * f = create_f(LWI);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument reg1;
                    reg1.Register = num_reg(lexem_arg1);
                    AddArg(f -> args, reg1);

                    Lexem * lexem_arg2 = GetNextToken();
                    i++;
                    Argument imm;
                    imm.num = atoi(lexem_arg2 -> name);
                    AddArg(f -> args, imm);

                    Lexem * lexem_arg3 = GetNextToken();
                    i++;
                    Argument reg2;
                    reg2.Register = num_reg(lexem_arg3);
                    AddArg(f -> args, reg2);

                    AddInstr(f);
                }
                if (!strcmp(lexem -> name, "ADDF")) {
                    Instr * f = create_f(ADDF);
                    for (int j = 0; j < 3; j++) {
                        Lexem * lexem_arg = GetNextToken();
                        i++;
                        Argument reg;
                        reg.Register = num_reg(lexem_arg);
                        AddArg(f -> args, reg);
                    }
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "PRINT")) {
                    Instr * f = create_f(PRINT);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "PRINTMEM")) {
                    Instr * f = create_f(PRINTMEM);
                    Lexem * lexem_arg = GetNextToken();
                    i++;
                    Argument arg;
                    arg.num = atoi(lexem_arg -> name);
                    AddArg(f -> args, arg);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "CALL")) {
                    Instr * f = create_f(CALL);
                    Lexem * lexem_arg1 = GetNextToken();
                    i++;
                    Argument arg_idx;
                    arg_idx.flag_name = lexem_arg1 -> name;
                    AddArg(f -> args, arg_idx);
                    AddInstr(f);
                }

                if (!strcmp(lexem -> name, "RET")) {
                    Instr * f = create_f(RET);
                    AddInstr(f);
                }

                break;

            case NUMBER:
                break;

            case REGISTER:
                break;

            case PARAN_OPEN:
                break;

            case PARAN_CLOSE:
                break;

        }
    }
}