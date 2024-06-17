#ifndef _INTERMEDIATE_H
#define _INTERMEDIATE_H

#include "lib.h"
#include "semantic.h"

int structErrorCnt;

void intermediateCode(Node* root_, char* filename);
// High-level Definitions
void translateProgram(Node* cur);
void translateExtDefList(Node* cur);
void translateExtDef(Node* cur);
void translateExtDecList(Node* cur);
// Declarators
void translateVarDec(Node* cur);
void translateParamVarDec(Node* cur);
void translateFunDec(Node* cur);
void translateVarList(Node* cur);
void translateParamDec(Node* cur);
// Statements
void translateCompSt(Node* cur);
void translateStmtList(Node* cur);
void translateStmt(Node* cur);
// Local Definitions
void translateDefList(Node* cur);
void translateDef(Node* cur);
void translateDecList(Node* cur);
void translateDec(Node* cur);
// Expressions
void translateExp(Node* cur, Operand place);
void translateExpBool(Node* cur, Operand place);
void translateExpNum(Node* cur, Operand place);
void translateExpArray(Node* cur, Operand place);
void translateExpFunc(Node* cur, Operand place);
ArgNode translateArgs(Node* cur);

void translateCond(Node* cur, Operand trueLabel, Operand falseLabel);
void printOprand(FILE* p, Operand op);
void printInterCode(FILE* p, InterCode code);
void writeCode2File(char* filename);

#endif