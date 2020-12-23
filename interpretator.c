#include "interpretator.h"


int registers[NUM_REGS] = {};

// 4 * 4096 [byte]
int memory[0x1000] = {};

int stack[1000] = {};

int stackpointer = 0;

void print_registers_inline() {
    for (int i = 0; i < NUM_REGS; ++i) {
        printf("R%d: %d| ", i, registers[i]);
    }
    printf("\n");
}

void print_mem(int n) {
    printf("memory: ");
    for (int i = 0; i < n; i++)
        printf("%d ", memory[i]);
    printf("\n");
}

void Ecall() {
    int syscall = registers[5];
    switch (syscall) {
        case 1:
            //print int
            printf("%d", registers[0]);
            break;
        case 2:
            // print float
            printf("%f", *((float * ) registers));
            break;
        case 3:
            // print char
            printf("%c", *((char * ) registers));

            break;
        case 4: {
            //read int
            int temp;
            scanf("%d", & temp);
            registers[0] = temp;
            break;
        }
        case 5: {
            // read float
            float temp;
            scanf("%f", & temp);
            registers[0] = * ((int * )( & temp));
            break;
        }
        case 6: {
            //read char
            char temp;
            scanf("%c", & temp);
            registers[0] = * ((int * )( & temp));
            break;
        }
        case 7: {
            // print space
            printf(" ");
            break;
        }
        case 8: {
            printf("\n");
            break;
        }
        default:
            break;

    }
}

void interpret() {
    for (int i = 0; i < getnumInstr(); i++) {
        Instr * currentInstr = getExecLine()[i];
        switch (currentInstr -> insturction) {
            case LI: {
                int reg = GetArg(currentInstr -> args, 0).Register;
                int num = GetArg(currentInstr -> args, 1).num;
                registers[reg] = num;
                break;
            }
            case ADD: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                registers[reg0] = registers[reg1] + registers[reg2];
                break;
            }
            case ADDI: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int num = GetArg(currentInstr -> args, 2).num;
                registers[reg0] = registers[reg1] + num;
                break;
            }
            case SUB: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                registers[reg0] = registers[reg1] - registers[reg2];
                break;
            }
            case NEG: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                registers[reg0] = -registers[reg1];
                break;
            }
            case DIV: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                registers[reg0] = registers[reg1] / registers[reg2];
                break;
            }
            case REM: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                registers[reg0] = registers[reg1] % registers[reg2];
                break;
            }
            case MUL: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                registers[reg0] = registers[reg1] * registers[reg2];
                break;
            }
            case MV: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                registers[reg0] = registers[reg1];
                break;
            }
            case ECALL: {
                Ecall();
                break;
            }
            case BEQ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] == registers[reg1])
                    i = idx;
                break;
            }
            case BNE: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] != registers[reg1])
                    i = idx;
                break;
            }
            case BLT: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] < registers[reg1])
                    i = idx;
                break;
            }
            case BGT: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] > registers[reg1])
                    i = idx;
                break;
            }
            case BLE: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] <= registers[reg1])
                    i = idx;
                break;
            }
            case BGE: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                char * flagname = GetArg(currentInstr -> args, 2).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] >= registers[reg1])
                    i = idx;
                break;
            }
            case BEQZ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                char * flagname = GetArg(currentInstr -> args, 1).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] == 0)
                    i = idx;
                break;
            }
            case BNEZ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                char * flagname = GetArg(currentInstr -> args, 1).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] != 0)
                    i = idx;
                break;
            }
            case BGTZ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                char * flagname = GetArg(currentInstr -> args, 1).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] > 0)
                    i = idx;
                break;
            }
            case BLEZ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                char * flagname = GetArg(currentInstr -> args, 1).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] <= 0)
                    i = idx;
                break;
            }
            case BGEZ: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                char * flagname = GetArg(currentInstr -> args, 1).flag_name;
                int idx = FindFlag(flagname);
                if (registers[reg0] >= 0)
                    i = idx;
                break;
            }
            case JUMP: {
                char * flagname = GetArg(currentInstr -> args, 0).flag_name;
                int idx = FindFlag(flagname);
                if (idx != -1)
                    i = idx;
                break;
            }
            case ARTEM: {
                for (int j = 0; j < NUM_REGS; j++)
                    registers[j] = 299792458;
                break;
            }
            case SWI: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int imm = GetArg(currentInstr -> args, 1).num;
                int reg1 = GetArg(currentInstr -> args, 2).Register;
                if (reg0 + imm > 0x1000) {
                    printf("Out of memory");
                    exit(1);
                }
                memory[registers[reg0] + imm] = registers[reg1];
                break;
            }
            case LWI: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int imm = GetArg(currentInstr -> args, 1).num;
                int reg1 = GetArg(currentInstr -> args, 2).Register;
                if (reg0 + imm > 0x1000) {
                    printf("Out of memory");
                    exit(1);
                }
                registers[reg1] = memory[registers[reg0] + imm];
                break;
            }
            case ADDF: {
                int reg0 = GetArg(currentInstr -> args, 0).Register;
                int reg1 = GetArg(currentInstr -> args, 1).Register;
                int reg2 = GetArg(currentInstr -> args, 2).Register;
                // to be continued
                break;
            }
            case PRINT: {
                print_registers_inline();
                break;
            }
            case PRINTMEM: {
                int num = GetArg(currentInstr -> args, 0).num;
                print_mem(num);
                break;
            }
            case CALL: {

                char * flagname = GetArg(currentInstr -> args, 0).flag_name;
                int label_idx = FindFlag(flagname);
                int next_idx = i;
                stack[stackpointer] = next_idx;

                stackpointer++;
                if (label_idx != -1)
                    i = label_idx;
                break;
            }
            case RET: {
                int idx = stack[--stackpointer];
                i = idx;
                break;
            }
            case FLAG_INST:
                break;

        }
    }
}