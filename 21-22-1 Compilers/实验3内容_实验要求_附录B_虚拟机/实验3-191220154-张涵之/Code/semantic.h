#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include "lib.h"

int semanticErrorCnt;

void printErrorMsg(int errorType_, int lineno, char* msg);
int semanticCheck(Node* root_);
// High-level Definitions
void Program(Node* cur);
void ExtDefList(Node* cur);
void ExtDef(Node* cur);
void ExtDecList(Node* cur, Type extDecType);
// Specifiers
Type Specifier(Node* cur);
Type StructSpecifier(Node* cur);
char* OptTag(Node* cur);
Type Tag(Node* cur);
// Declarators
Symbol VarDec(Node* cur, Type varDecType);
Symbol StructVarDec(Node* cur, Type varDecType);
void FunDec(Node* cur, Type funcDecType);
FieldList VarList(Node* cur);
FieldList ParamDec(Node* cur);
// Statements
void CompSt(Node* cur, Type compStType);
void StmtList(Node* cur, Type stmtType);
void Stmt(Node* cur, Type stmtType);
// Local Definitions
void DefList(Node* cur);
FieldList StructDefList(Node* cur);
void Def(Node* cur);
FieldList StructDef(Node* cur);
void DecList(Node* cur, Type decType);
FieldList StructDecList(Node* cur, Type decType);
void Dec(Node* cur, Type decType);
FieldList StructDec(Node* cur, Type decType);
// Expressions
Type Exp(Node* cur);
FieldList Args(Node* cur);

#endif