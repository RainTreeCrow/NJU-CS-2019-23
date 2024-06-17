#include "intermediate.h"

int structErrorCnt = 0;

int intermediateCode(Node* root_) {
    interCodeHead = NULL;
    interCodeTail = NULL;
    argAddrList = NULL;
    variableIndex = 1;
    tempvarIndex = 1;
    labelIndex = 1;
    translateProgram(root_);
    if (structErrorCnt != 0) {
		printf("Cannot translate: Code contains variables or parameters of structure type.\n");
        return 0;
    }
    else {
        //writeCode2File(filename);
        return 1;
    }
}

// High-level Definitions
void translateProgram(Node* cur) {
    translateExtDefList(getChild(cur, 1));
}

void translateExtDefList(Node* cur) {
    if (cur->child != NULL) {
        translateExtDef(getChild(cur, 1));
        translateExtDefList(getChild(cur, 2));
    }
}

void translateExtDef(Node* cur) {
    Node* q = getChild(cur, 2);
    if (strcmp(q->name, "FunDec") == 0) {
        translateFunDec(q);
        translateCompSt(getChild(cur, 3));
    }
    else if (strcmp(q->name, "ExtDecList") == 0)
        translateExtDecList(q);
}

void translateExtDecList(Node* cur) {
    translateVarDec(getChild(cur, 1));
    if (getChild(cur, 2) != NULL)
        translateExtDecList(getChild(cur, 3));
}

// Declarators
void translateVarDec(Node* cur) {
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "ID") == 0) {
        Symbol sym = lookUpTable(p->val, SymbolTable);
        if (sym->type->kind == STRUCTURE)
            structErrorCnt++;
        else {
            int size = calcSize(sym->type);
            char varName[32];
            if (sym->varIndex == -1)
                sym->varIndex = variableIndex++;
            //printf("FuncVarDec v%d\n", sym->varIndex);
            sprintf(varName, "v%d", sym->varIndex);
            Operand op = newOperand(VARIABLE, varName);
            if (sym->type->kind == ARRAY) {
                InterCode code = newInterCode(_DEC, op, size);
                insertCode(code);
                //printf("DEC\n");
            }
        }
    }
    else
        translateVarDec(p);
}

void translateParamVarDec(Node* cur) {
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "ID") == 0) {
        Symbol sym = lookUpTable(p->val, SymbolTable);
        if (sym->type->kind == STRUCTURE)
            structErrorCnt++;
        else {
            char varName[32];
            if (sym->varIndex == -1)
                sym->varIndex = variableIndex++;
                //printf("FuncVarDec v%d\n", sym->varIndex);
            sprintf(varName, "v%d", sym->varIndex);
            Operand op = newOperand(VARIABLE, varName);
            InterCode code = newInterCode(_PARAM, op);
            insertCode(code);
            if (sym->type->kind == ARRAY) {
                ArgAddr newArg = (ArgAddr)malloc(sizeof(struct ArgAddr_));
                strcpy(newArg->name, varName);
                newArg->next = argAddrList;
                argAddrList = newArg;
            }
        }
    }
    else
        translateParamVarDec(p);
}

void translateFunDec(Node* cur) {
    Node* p = getChild(cur, 1);
    Operand op = newOperand(VARIABLE, p->val);
    InterCode code = newInterCode(_FUNC, op);
    insertCode(code);
    if (getChild(cur, 4) != NULL) {
        Node* q = getChild(cur, 3);
        translateVarList(q);
    }
}

void translateVarList(Node* cur) {
    Node* p = getChild(cur, 1);
    translateParamDec(p);
    Node* q = getChild(cur, 2);
    if (q != NULL)
        translateVarList(getChild(cur, 3));
}

void translateParamDec(Node* cur) {
    translateParamVarDec(getChild(cur, 2));
}

// Statements
void translateCompSt(Node* cur) {
    Node* p = getChild(cur, 2);
    Node* q = getChild(cur, 3);
    if (strcmp(p->name, "DefList") == 0)
        translateDefList(p);
    if (strcmp(q->name, "StmtList") == 0)
        translateStmtList(q);
}

void translateStmtList(Node* cur) {
    if (cur->child != NULL) {
        translateStmt(getChild(cur, 1));
        translateStmtList(getChild(cur, 2));
    }
}

void translateStmt(Node* cur) {
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "Exp") == 0) {
        Operand op = newOperand(OTHER);
        translateExp(p, op);
    }
    else if (strcmp(p->name, "CompSt") == 0)
        translateCompSt(p);
    else if (strcmp(p->name, "RETURN") == 0) {
        Operand ot = newOperand(OTHER);
        translateExp(getChild(cur, 2), ot);
        InterCode code;
        Operand op;
        if (ot->kind != CONSTANT && ot->kind != TEMPVAR && ot->kind != VARIABLE) {
            op = newOperand(TEMPVAR);
            code = newInterCode(_ASSIGN, op, ot);
            insertCode(code);
        }
        else
            op = ot;
        code = newInterCode(_RETURN, op);
        insertCode(code);
    }
    else if (strcmp(p->name, "IF") == 0) {
        if (getChild(cur, 6) == NULL) {
            Operand trueLabel = newOperand(LABEL);
            Operand falseLabel = newOperand(LABEL);
            translateCond(getChild(cur, 3), trueLabel, falseLabel);
            InterCode code = newInterCode(_LABEL, trueLabel);
            insertCode(code);
            translateStmt(getChild(cur, 5));
            code = newInterCode(_LABEL, falseLabel);
            insertCode(code);
        }
        else {
            Operand trueLabel = newOperand(LABEL);
            Operand falseLabel = newOperand(LABEL);
            Operand endLabel = newOperand(LABEL);
            translateCond(getChild(cur, 3), trueLabel, falseLabel);
            InterCode code = newInterCode(_LABEL, trueLabel);
            insertCode(code);
            translateStmt(getChild(cur, 5));
            code = newInterCode(_GOTO, endLabel);
            insertCode(code);
            code = newInterCode(_LABEL, falseLabel);
            insertCode(code);
            translateStmt(getChild(cur, 7));
            code = newInterCode(_LABEL, endLabel);
            insertCode(code);
        }
    }
    else if (strcmp(p->name, "WHILE") == 0) {
        Operand backLabel = newOperand(LABEL);
        Operand trueLabel = newOperand(LABEL);
        Operand falseLabel = newOperand(LABEL);
        InterCode code = newInterCode(_LABEL, backLabel);
        insertCode(code);
        translateCond(getChild(cur, 3), trueLabel, falseLabel);
        code = newInterCode(_LABEL, trueLabel);
        insertCode(code);
        translateStmt(getChild(cur, 5));
        code = newInterCode(_GOTO, backLabel);
        insertCode(code);
        code = newInterCode(_LABEL, falseLabel);
        insertCode(code);
    }
}

// Local Definitions
void translateDefList(Node* cur) {
    if (cur->child != NULL) {
        translateDef(getChild(cur, 1));
        translateDefList(getChild(cur, 2));
    }
}

void translateDef(Node* cur) {
    translateDecList(getChild(cur, 2));
}

void translateDecList(Node* cur) {
    translateDec(getChild(cur, 1));
    if (getChild(cur, 2) != NULL)
        translateDecList(getChild(cur, 3));
}

void translateDec(Node* cur) {
    Node* p = getChild(cur, 2);
    if (p == NULL) {
        translateVarDec(getChild(cur, 1));
    }
    else {
        Node* vardec = getChild(cur, 1);
        translateVarDec(vardec);
        if (getChild(vardec, 2) != NULL)
            return;
        Node* id = getChild(vardec, 1);
        Symbol sym = lookUpTable(id->val, SymbolTable);
        char varName[32];
        if (sym->varIndex == -1)
            sym->varIndex = variableIndex++;
        sprintf(varName, "v%d", sym->varIndex);
        //printf("Dec v%d\n", sym->varIndex);
        Operand left = newOperand(VARIABLE, varName);
        Operand val = newOperand(OTHER);
        Operand right;
        InterCode code;
        translateExp(getChild(cur, 3), val);
        if (val->kind != CONSTANT && val->kind != TEMPVAR && val->kind != VARIABLE) {
            right = newOperand(TEMPVAR);
            code = newInterCode(_ASSIGN, right, val);
            insertCode(code);
        }
        else
            right = val;
        code = newInterCode(_ASSIGN, left, right);
        insertCode(code);
    }
}

// Expressions
void translateExp(Node* cur, Operand place) {
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "Exp") == 0) {
        Node* q = getChild(cur, 2);
        if (strcmp(q->name, "ASSIGNOP") == 0) {
            Node* r = getChild(cur, 3);
            Operand left = newOperand(OTHER);
            translateExp(p, left);
            Operand right = newOperand(OTHER);
            translateExp(r, right);
            Type leftType = Exp(p);
            Type rightType = Exp(r);
            //printf("%d vs %d\n", leftType->kind, ARRAY);
            if (leftType->kind != ARRAY) {
                if (left->kind == OTHER) {
                    free(left);
                    left = newOperand(TEMPVAR);
                }
                InterCode code = newInterCode(_ASSIGN, left, right);
                insertCode(code);
            }
            else
                return;
        }
        else if (strcmp(q->name, "AND") == 0 || strcmp(q->name, "OR") == 0 || strcmp(q->name, "RELOP") == 0)
            translateExpBool(cur, place);
        else if (strcmp(q->name, "PLUS") == 0 || strcmp(q->name, "MINUS") == 0
            || strcmp(q->name, "STAR") == 0 || strcmp(q->name, "DIV") == 0)
            translateExpNum(cur, place);
        else if (strcmp(q->name, "LB") == 0)
            translateExpArray(cur, place);
        else if (strcmp(q->name, "DOT") == 0)
            structErrorCnt++;
    }
    else if (strcmp(p->name, "LP") == 0) {
        Node* q = getChild(cur, 2);
        translateExp(q, place);
    }
    else if (strcmp(p->name, "MINUS") == 0) {
        Node* q = getChild(cur, 2);
        Operand zero = newOperand(CONSTANT, 0);
        Operand exp = newOperand(OTHER);
        translateExp(q, exp);
        if (place->kind == OTHER) {
            free(place);
            place = newOperand(TEMPVAR);
        }
        InterCode code = newInterCode(_SUB, place, zero, exp);
        insertCode(code);
    }
    else if (strcmp(p->name, "NOT") == 0)
        translateExpBool(cur, place);
    else if (strcmp(p->name, "ID") == 0) {
        Node* q = getChild(cur, 2);
        if (q == NULL) {
            Symbol idSym = lookUpTable(p->val, SymbolTable);
            char varName[32];
            if (idSym->varIndex == -1)
                idSym->varIndex = variableIndex++;
            sprintf(varName, "v%d", idSym->varIndex);
            //printf("Exp ID v%d\n", idSym->varIndex);
            strcpy(place->u.value, varName);
            if (idSym->type->kind == ARRAY) {
                place->kind = ADDRESS;
                ArgAddr temp = argAddrList;
                while (temp != NULL) {
                    if (strcmp(varName, temp->name) == 0)
                        break;
                    temp = temp->next;
                }
                if (temp != NULL)
                    place->kind = VARIABLE;
            }
            else
                place->kind = VARIABLE;
        }
        else
            translateExpFunc(cur, place);
    }
    else if (strcmp(p->name, "INT") == 0) {
        place->kind = CONSTANT;
        place->u.var = atoi(p->val);
        //printf("Constant int\n");
    }
}

void translateExpBool(Node* cur, Operand place) {
    Operand labeltrue = newOperand(LABEL);
    Operand labelfalse = newOperand(LABEL);
    Operand zero = newOperand(CONSTANT, 0);
    Operand one = newOperand(CONSTANT, 1);
    if (place->kind == OTHER) {
        free(place);
        place = newOperand(TEMPVAR);
    }
    InterCode code = newInterCode(_ASSIGN, place, zero);
    insertCode(code);
    translateCond(cur, labeltrue, labelfalse);
    code = newInterCode(_LABEL, labeltrue);
    insertCode(code);
    code = newInterCode(_ASSIGN, place, one);
    insertCode(code);
    code = newInterCode(_LABEL, labelfalse);
    insertCode(code);
}

void translateExpNum(Node* cur, Operand place) {
    if (place->kind == OTHER) {
        free(place);
        place = newOperand(TEMPVAR);
    }
    Node* p = getChild(cur, 1);
    Node* q = getChild(cur, 2);
    Node* r = getChild(cur, 3);
    Operand op1 = newOperand(OTHER);
    translateExp(p, op1);
    Operand op2 = newOperand(OTHER);
    translateExp(r, op2);
    InterCode code;
    if (strcmp(q->name, "PLUS") == 0) {
        code = newInterCode(_ADD, place, op1, op2);
        insertCode(code);
    }
    else if (strcmp(q->name, "MINUS") == 0) {
        code = newInterCode(_SUB, place, op1, op2);
        insertCode(code);
    }
    else if (strcmp(q->name, "STAR") == 0) {
        code = newInterCode(_MUL, place, op1, op2);
        insertCode(code);
    }
    else if (strcmp(q->name, "DIV") == 0) {
        code = newInterCode(_DIV, place, op1, op2);
        insertCode(code);
    }
}

void translateExpArray(Node* cur, Operand place) {
    Operand base = newOperand(TEMPVAR);
    Operand index = newOperand(TEMPVAR);
    Operand offset = newOperand(TEMPVAR);
    Operand address = newOperand(TEMPVAR);
    Node* p = getChild(cur, 1);
    if (base->kind == POINTER)
        base->kind = TEMPVAR;
    translateExp(p, base);
    Node* r = getChild(cur, 3);
    translateExp(r, index);
    Type type = Exp(p);
    Operand size = newOperand(CONSTANT, calcSize(type->u.array.elem));
    InterCode code = newInterCode(_MUL, offset, index, size);
    insertCode(code);
    code = newInterCode(_ADD, address, base, offset);
    insertCode(code);
    place->kind = POINTER;
    strcpy(place->u.value, address->u.value);
}

void translateExpFunc(Node* cur, Operand place) {
    Node* p = getChild(cur, 1);
    Node* r = getChild(cur, 3);
    char funcName[32];
    strcpy(funcName, p->val);
    Symbol sym = lookUpTable(funcName, SymbolTable);
    if (place->kind == OTHER) {
        free(place);
        place = newOperand(TEMPVAR);
    }
    InterCode code;
    if (strcmp(r->name, "Args") == 0) {
        ArgNode argList = NULL;
        argList = translateArgs(r);
        if (strcmp(funcName, "write") == 0) {
            code = newInterCode(_WRITE, argList->op);
            insertCode(code);
        }
        else {
            ArgNode p = argList;
            while (p) {
                code = newInterCode(_ARG, p->op);
                insertCode(code);
                p = p->next;
            }
            Operand func = newOperand(FUNC, funcName);
            code = newInterCode(_CALL, place, func);
            insertCode(code);
        }
    }
    else {
        if (strcmp(funcName, "read") == 0) {
            code = newInterCode(_READ, place);
            insertCode(code);
        }
        else {
            Operand func = newOperand(FUNC, funcName);
            code = newInterCode(_CALL, place, func);
            insertCode(code);
        }
    }

}

ArgNode translateArgs(Node* cur) {
    ArgNode argListHead = NULL;
    Node* p = getChild(cur, 1);
    Node* q = getChild(cur, 2);
    if (q != NULL)
        argListHead = translateArgs(getChild(cur, 3));
    Operand ot = newOperand(OTHER);
    translateExp(p, ot);
    InterCode code;
    Operand op;
    if (ot->kind != CONSTANT && ot->kind != TEMPVAR && ot->kind != VARIABLE) {
        op = newOperand(TEMPVAR);
        code = newInterCode(_ASSIGN, op, ot);
        insertCode(code);
    }
    else
        op = ot;
    ArgNode tempNode = (ArgNode)malloc(sizeof(struct ArgNode_));
    tempNode->op = op;
    tempNode->next = NULL;
    if (argListHead == NULL)
        argListHead = tempNode;
    else {
        ArgNode argListTail = argListHead;
        while (argListTail->next != NULL)
            argListTail = argListTail->next;
        argListTail->next = tempNode;
    }
    return argListHead;
}

void translateCond(Node* cur, Operand trueLabel, Operand falseLabel) {
    Node* p = getChild(cur, 1);
    Node* q = getChild(cur, 2);
    Node* r = getChild(cur, 3);
    if (p && strcmp(p->name, "LP") == 0)
        translateCond(q, trueLabel, falseLabel);
    else if (p && strcmp(p->name, "NOT") == 0)
        translateCond(q, falseLabel, trueLabel);
    else if (q && strcmp(q->name, "RELOP") == 0) {
        Operand x;
        Operand y;
        Operand otx = newOperand(OTHER);
        Operand oty = newOperand(OTHER);
        translateExp(p, otx);
        translateExp(r, oty);
        InterCode code;
        if (otx->kind != CONSTANT && otx->kind != TEMPVAR && otx->kind != VARIABLE) {
            x = newOperand(TEMPVAR);
            code = newInterCode(_ASSIGN, x, otx);
            insertCode(code);
        }
        else
            x = otx;
        if (oty->kind != CONSTANT && oty->kind != TEMPVAR && oty->kind != VARIABLE) {
            y = newOperand(TEMPVAR);
            code = newInterCode(_ASSIGN, y, oty);
            insertCode(code);
        }
        else
            y = oty;
        code = newInterCode(_IFGOTO, x, y, trueLabel, q->val);
        insertCode(code);
        code = newInterCode(_GOTO, falseLabel);
        insertCode(code);
    }
    else if (q && strcmp(q->name, "AND") == 0) {
        Operand label = newOperand(LABEL);
        translateCond(p, label, falseLabel);
        InterCode code = newInterCode(_LABEL, label);
        insertCode(code);
        translateCond(r, trueLabel, falseLabel);
    }
    else if (q && strcmp(q->name, "OR") == 0) {
        Operand label = newOperand(LABEL);
        translateCond(p, trueLabel, label);
        InterCode code = newInterCode(_LABEL, label);
        insertCode(code);
        translateCond(r, trueLabel, falseLabel);
    }
    else {
        Operand op = newOperand(OTHER);
        translateExp(cur, op);
        Operand zero = newOperand(CONSTANT, 0);
        InterCode code = newInterCode(_IFGOTO, op, zero, trueLabel, "==");
        insertCode(code);
        code = newInterCode(_GOTO, falseLabel);
        insertCode(code);
    }
}

void printOprand(FILE* fp, Operand op) {
    switch (op->kind) {
        case VARIABLE:
        case TEMPVAR:
        case LABEL:
        case FUNC:
            fprintf(fp, "%s", op->u.value);
            break;
        case CONSTANT:
            fprintf(fp, "#%d", op->u.var);
            break;
        case ADDRESS:
            fprintf(fp, "&%s", op->u.value);
            break;
        case POINTER:
            fprintf(fp, "*%s", op->u.value);
            break;
        case OTHER:
            break;
        default:
            break;
    }
}

void printInterCode(FILE* fp, InterCode code) {
    switch (code->kind) {
        case _LABEL:
            fprintf(fp, "LABEL ");
            printOprand(fp, code->u.sinop.op);
            fprintf(fp, " :");
            break;
        case _FUNC:
            fprintf(fp, "FUNCTION ");
            printOprand(fp, code->u.sinop.op);
            fprintf(fp, " :");
            break;
        case _ASSIGN:
            printOprand(fp, code->u.assign.left);
            fprintf(fp, " := ");
            printOprand(fp, code->u.assign.right);
            break;
        case _ADD:
            printOprand(fp, code->u.binop.result);
            fprintf(fp, " := ");
            printOprand(fp, code->u.binop.op1);
            fprintf(fp, " + ");
            printOprand(fp, code->u.binop.op2);
            break;
        case _SUB:
            printOprand(fp, code->u.binop.result);
            fprintf(fp, " := ");
            printOprand(fp, code->u.binop.op1);
            fprintf(fp, " - ");
            printOprand(fp, code->u.binop.op2);
            break;
        case _MUL:
            printOprand(fp, code->u.binop.result);
            fprintf(fp, " := ");
            printOprand(fp, code->u.binop.op1);
            fprintf(fp, " * ");
            printOprand(fp, code->u.binop.op2);
            break;
        case _DIV:
            printOprand(fp, code->u.binop.result);
            fprintf(fp, " := ");
            printOprand(fp, code->u.binop.op1);
            fprintf(fp, " / ");
            printOprand(fp, code->u.binop.op2);
            break;
        case _GOTO:
            fprintf(fp, "GOTO ");
            printOprand(fp, code->u.sinop.op);
            break;
        case _IFGOTO:
            fprintf(fp, "IF ");
            printOprand(fp, code->u.ifgoto.x);
            fprintf(fp, " %s ", code->u.ifgoto.relop);
            printOprand(fp, code->u.ifgoto.y);
            fprintf(fp, " GOTO ");
            printOprand(fp, code->u.ifgoto.z);
            break;
        case _RETURN:
            fprintf(fp, "RETURN ");
            printOprand(fp, code->u.sinop.op);
            //fprintf(fp, "\n");
            break;
        case _DEC:
            fprintf(fp, "DEC ");
            printOprand(fp, code->u.dec.op);
            fprintf(fp, " %d", code->u.dec.size);
            break;
        case _ARG:
            fprintf(fp, "ARG ");
            printOprand(fp, code->u.sinop.op);
            break;
        case _CALL:
            printOprand(fp, code->u.assign.left);
            fprintf(fp, " := CALL ");
            printOprand(fp, code->u.assign.right);
            break;
        case _PARAM:
            fprintf(fp, "PARAM ");
            printOprand(fp, code->u.sinop.op);
            break;
        case _READ:
            fprintf(fp, "READ ");
            printOprand(fp, code->u.sinop.op);
            break;
        case _WRITE:
            fprintf(fp, "WRITE ");
            printOprand(fp, code->u.sinop.op);
            break;
        default:
            break;
    }
}

void writeCode2File(char* filename) {
    FILE *fp;
    fp = fopen(filename, "w+");
    if (fp == NULL) return;
    InterCode code = interCodeHead;
    while (code != NULL) {
        printInterCode(fp, code);
        fprintf(fp, "\n");
        code = code->next;
    }
}