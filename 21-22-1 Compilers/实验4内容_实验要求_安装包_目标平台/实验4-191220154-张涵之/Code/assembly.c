#include "assembly.h"

void assembly(char* filename) {
    initMemoryBlock();
    freeAllTReg();
    stack_fp = 10000;
    stack_sp = 10000;
    paramCnt = 0;
    FILE *fp;
    fp = fopen(filename, "w+");
    if (fp == NULL) return;
    //printf("Hello\n");
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0, 1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0, $0\n");
    fprintf(fp, "  jr $ra\n");
    InterCode cur = interCodeHead;
    while (cur != NULL) {
        assembleCode(fp, cur);
        freeAllTReg();
        cur = cur->next;
    }
}

void assembleCode(FILE* p, InterCode code) {
    if (code->kind != _PARAM && paramCnt > 0)
        paramCnt = 0;
    switch (code->kind) {
        case _LABEL: assembleLabel(p, code); break;
        case _FUNC: assembleFunc(p, code); break;
        case _ASSIGN: assembleAssign(p, code); break;
        case _ADD:
        case _SUB:
        case _MUL:
        case _DIV: assembleBinary(p, code); break;
        case _GOTO: assembleGoto(p, code); break;
        case _IFGOTO: assembleIfgoto(p, code); break;
        case _RETURN: assembleReturn(p, code); break;
        case _DEC: assembleDec(p, code); break;
        case _ARG: assembleArg(p, code); break;
        case _CALL: assembleCall(p, code); break;
        case _PARAM: assembleParam(p, code); break;
        case _READ: assembleRead(p, code); break;
        case _WRITE: assembleWrite(p, code); break;
        default: break;
    }
}

void assembleLabel(FILE* p, InterCode code) {
    fprintf(p, "%s:\n", code->u.sinop.op->u.value);
    genAssemblyCode(p, ADDI_, "$sp", "$fp", stack_sp - stack_fp);
}

void assembleFunc(FILE* p, InterCode code) {
    stack_fp = 10000;
    stack_sp = 10000;
    fprintf(p, "\n%s:\n", code->u.sinop.op->u.value);
    genAssemblyCode(p, ADDI_, "$sp", "$sp", -4);
    stack_sp = stack_sp - 4;
    genAssemblyCode(p, SW_, "$fp", 0, "$sp");
    genAssemblyCode(p, MOVE_, "$fp", "$sp");
    stack_fp = stack_fp - 4;
    genAssemblyCode(p, ADDI_, "$sp", "$sp", -4);
    stack_sp = stack_sp - 4;
    genAssemblyCode(p, SW_, "$ra", 0, "$sp");
}

void assembleAssign(FILE* p, InterCode code) {
    Operand left = code->u.assign.left;
    Operand right = code->u.assign.right;
    char* leftReg = findLeftReg(p, left);
    char* rightReg = findRightReg(p, right);
    if (left->kind == POINTER) {
        if (right->kind == CONSTANT)
            genAssemblyCode(p, LI_, rightReg, right->u.var);
        genAssemblyCode(p, SW_, rightReg, 0, leftReg);
    }
    else {
        if (right->kind == CONSTANT)
            genAssemblyCode(p, LI_, leftReg, right->u.var);
        else
            genAssemblyCode(p, MOVE_, leftReg, rightReg);
        genAssemblyCode(p, SW_, leftReg, lookUpBlock(left->u.value)->fpOffset, "$fp");
    }
}

void assembleBinary(FILE* p, InterCode code) {
    Operand op1 = code->u.binop.op1;
    Operand op2 = code->u.binop.op2;
    Operand result = code->u.binop.result;
    char* op1Reg = findRightReg(p, op1);
    char* op2Reg = findRightReg(p, op2);
    char* resultReg = findLeftReg(p, result);
    if (result->kind == POINTER) {
        if (code->kind == _ADD) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, op1Reg, op1->u.var + op2->u.var);
            else if (op1->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, op1Reg, op2Reg, op1->u.var);
            else if (op2->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, op1Reg, op1Reg, op2->u.var);
            else
                genAssemblyCode(p, ADD_, op1Reg, op1Reg, op2Reg);
        }
        else if (code->kind == _SUB) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, op1Reg, op1->u.var - op2->u.var);
            else if (op1->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
                genAssemblyCode(p, SUB_, op1Reg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, op1Reg, op1Reg, -op2->u.var);
            else
                genAssemblyCode(p, SUB_, op1Reg, op1Reg, op2Reg);
        }
        else if (code->kind == _MUL) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, op1Reg, op1->u.var * op2->u.var);
            else if (op1->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
                genAssemblyCode(p, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op2Reg, op2->u.var);
                genAssemblyCode(p, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else
                genAssemblyCode(p, MUL_, op1Reg, op1Reg, op2Reg);
        }
        else if (code->kind == _DIV) {
            if (op1->kind == CONSTANT)
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
            if (op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, op2Reg, op2->u.var);
            genAssemblyCode(p, DIV__, op1Reg, op2Reg, op1Reg);
        }
        genAssemblyCode(p, SW_, op1Reg, 0, resultReg);
    }
    else if (result->kind == VARIABLE || result->kind == TEMPVAR) {
        if (code->kind == _ADD) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, resultReg, op1->u.var + op2->u.var);
            else if (op1->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, resultReg, op2Reg, op1->u.var);
            else if (op2->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, resultReg, op1Reg, op2->u.var);
            else
                genAssemblyCode(p, ADD_, resultReg, op1Reg, op2Reg);
        }
        else if (code->kind == _SUB) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, resultReg, op1->u.var - op2->u.var);
            else if (op1->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
                genAssemblyCode(p, SUB_, resultReg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT)
                genAssemblyCode(p, ADDI_, resultReg, op1Reg, -op2->u.var);
            else
                genAssemblyCode(p, SUB_, resultReg, op1Reg, op2Reg);
        }
        else if (code->kind == _MUL) {
            if (op1->kind == CONSTANT && op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, resultReg, op1->u.var * op2->u.var);
            else if (op1->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
                genAssemblyCode(p, MUL_, resultReg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT) {
                genAssemblyCode(p, LI_, op2Reg, op2->u.var);
                genAssemblyCode(p, MUL_, resultReg, op1Reg, op2Reg);
            }
            else
                genAssemblyCode(p, MUL_, resultReg, op1Reg, op2Reg);
        }
        else if (code->kind == _DIV) {
            if (op1->kind == CONSTANT)
                genAssemblyCode(p, LI_, op1Reg, op1->u.var);
            if (op2->kind == CONSTANT)
                genAssemblyCode(p, LI_, op2Reg, op2->u.var);
            genAssemblyCode(p, DIV__, op1Reg, op2Reg, resultReg);
        }
        genAssemblyCode(p, SW_, resultReg, lookUpBlock(result->u.value)->fpOffset, "$fp");
    }
}

void assembleGoto(FILE* p, InterCode code) {
    fprintf(p, "  j %s\n", code->u.sinop.op->u.value);
}

void assembleIfgoto(FILE* p, InterCode code) {
    char relop[5];
    Operand x = code->u.ifgoto.x;
    Operand y = code->u.ifgoto.y;
    Operand z = code->u.ifgoto.z;
    strcpy(relop, code->u.ifgoto.relop);
    char* xReg = findRightReg(p, x);
    char* yReg = findRightReg(p, y);
    if (x->kind == CONSTANT)
        genAssemblyCode(p, LI_, xReg, x->u.var);
    if (y->kind == CONSTANT)
        genAssemblyCode(p, LI_, yReg, y->u.var);
    if (strcmp(relop, "==") == 0)
        genAssemblyCode(p, BEQ_, xReg, yReg);
    else if (strcmp(relop, "!=") == 0)
        genAssemblyCode(p, BNE_, xReg, yReg);
    else if (strcmp(relop, ">") == 0)
        genAssemblyCode(p, BGT_, xReg, yReg);
    else if (strcmp(relop, "<") == 0)
        genAssemblyCode(p, BLT_, xReg, yReg);
    else if (strcmp(relop, ">=") == 0)
        genAssemblyCode(p, BGE_, xReg, yReg);
    else if (strcmp(relop, "<=") == 0)
        genAssemblyCode(p, BLE_, xReg, yReg);
    fprintf(p, "%s\n", z->u.value);
}

void assembleReturn(FILE* p, InterCode code) {
    Operand returnVar = code->u.sinop.op;
    if (returnVar->kind == CONSTANT)
        genAssemblyCode(p, LI_, "$v0", returnVar->u.var);
    else {
        char* returnReg = findRightReg(p, returnVar);
        genAssemblyCode(p, MOVE_, "$v0", returnReg);
    }
    genAssemblyCode(p, LW_, "$ra", -4, "$fp");
    fprintf(p, "  jr $ra\n");
}

void assembleDec(FILE* p, InterCode code) {
    Operand variable = code->u.dec.op;
    int arraySize = code->u.dec.size;
    fprintf(p, "  addi $sp, $sp, -%d\n", arraySize);
    stack_sp = stack_sp - arraySize;
    Memory mem = newMemory(variable->u.value, stack_sp - stack_fp);
    insertMemory(mem);
}

void assembleArg(FILE* p, InterCode code) {
    Operand arg = code->u.sinop.op;
    char* argReg = findRightReg(p, arg);
    if (arg->kind == CONSTANT)
        genAssemblyCode(p, LI_, argReg, arg->u.var);
    genAssemblyCode(p, ADDI_, "$sp", "$sp", -4);
    stack_sp = stack_sp - 4;
    genAssemblyCode(p, SW_, argReg, stack_sp - stack_fp, "$fp");
}

void assembleCall(FILE* p, InterCode code) {
    Operand assign = code->u.assign.left;
    Operand function = code->u.assign.right;
    fprintf(p, "  jal %s\n", function->u.value);
    genAssemblyCode(p, ADDI_, "$sp", "$fp", 4);
    genAssemblyCode(p, LW_, "$fp", 0, "$fp");
    char* leftReg = findLeftReg(p, assign);
    genAssemblyCode(p, MOVE_, leftReg, "$v0");
    if (assign->kind == POINTER)
        genAssemblyCode(p, SW_, "$v0", 0, leftReg);
    else
        genAssemblyCode(p, SW_, leftReg, lookUpBlock(assign->u.value)->fpOffset, "$fp");
}

void assembleParam(FILE* p, InterCode code) {
    Operand param = code->u.sinop.op;
    Memory mem = newMemory(param->u.value, (++paramCnt) * 4);
    insertMemory(mem);
}

void assembleRead(FILE* p, InterCode code) {
    Operand read = code->u.sinop.op;
    fprintf(p, "  jal read\n");
    char* readReg = findLeftReg(p, read);
    genAssemblyCode(p, MOVE_, readReg, "$v0");
    genAssemblyCode(p, SW_, readReg, lookUpBlock(read->u.value)->fpOffset, "$fp");
}

void assembleWrite(FILE* p, InterCode code) {
    Operand write = code->u.sinop.op;
    if (write->kind == CONSTANT)
        genAssemblyCode(p, LI_, "$a0", write->u.var);
    else {
        char* writeReg = findRightReg(p, write);
        genAssemblyCode(p, MOVE_, "$a0", writeReg);
    }
    fprintf(p, "  jal write\n");
}