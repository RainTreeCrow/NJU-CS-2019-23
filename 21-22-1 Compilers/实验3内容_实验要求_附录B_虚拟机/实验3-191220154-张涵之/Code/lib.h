#ifndef _LIB_H
#define _LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

typedef enum {
	INT_, FLOAT_, ID_, SEMI_, COMMA_,
	ASSIGNOP_, RELOP_,
	PLUS_, MINUS_, STAR_, DIV_,
	AND_, OR_, DOT_, NOT_, TYPE_,
	LP_, RP_, LB_, RB_, LC_, RC_,
	STRUCT_, RETURN_, IF_, ELSE_, WHILE_, COMPLEX_
} _Type;

typedef struct {
	char name[32];
	char val[32];
	int line;
	_Type type;
	struct Node* child;
	struct Node* next;
} Node;

Node* createNode(char n[], char v[], int l, _Type t);
void modifyTree(Node* cur, int cnt, ...);
void printNode(Node* cur);
void printTree(Node* root, int depth);
Node* getChild(Node* cur, int cnt);

Node* treeRoot;

#define BASIC_INT 0x0
#define BASIC_FLOAT 0x1
#define SYMTABLE_SIZE 0x3fff
#define FIELDLIST_SIZE 0x3f

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Symbol_* Symbol;

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE, FUNCTION, ERROR } kind;
    union {
        int basic;
        struct { Type elem; int size; } array;
        FieldList structure;
        struct { Type returnType; FieldList parameters; } function;
        int errorCode;
    } u;
};

struct FieldList_ {
    char name[32];
    Type type;
    int defineLine;
    FieldList tail;
};

struct Symbol_ {
    char name[32];
    Type type;
    int varIndex;
    int defineLine;
    Symbol hashTail;
};

Symbol* SymbolTable;

unsigned int hash_pjw(char* name_, int size_);
FieldList* creatFieldList();
Symbol* createSymbolTable();
Type basicType(int basic_);
Type arrayType(Type elem_, int size_);
Type structType(FieldList members_);
Type funcType(Type returnType_, FieldList parameters_);
Type errorType(int errorCode_);
int isInt(Type t);
int isFloat(Type t);
FieldList newField(char* name_, Type type_, int line_);
Symbol newSymbol(char* name_, Type type_, int line_);
int equalList(FieldList l1, FieldList l2);
int equalType(Type t1, Type t2);
void insertSymbol(Symbol symbol_, Symbol* table_);
Symbol lookUpTable(char* name_, Symbol* table_);
void freeSymbol(Symbol cur);
void delTable(Symbol* table_);
void printTable(Symbol* table_);

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct ArgNode_* ArgNode;
typedef struct ArgAddr_* ArgAddr;

struct Operand_ {
    enum { VARIABLE, TEMPVAR, CONSTANT, ADDRESS, POINTER, LABEL, FUNC, OTHER } kind;
    union {
        int var;
        char value[32];
    } u;
};

struct InterCode_ {
    enum { _LABEL, _FUNC, _ASSIGN, _ADD, _SUB, _MUL, _DIV,
        _GOTO, _IFGOTO, _RETURN, _DEC, _ARG, _CALL, _PARAM, _READ, _WRITE
    } kind;
    union {
        struct { Operand right, left; } assign;
        struct { Operand op; } sinop;
        struct { Operand result, op1, op2; } binop;
        struct { Operand x, y, z; char relop[5]; } ifgoto;
        struct { Operand op; int size; } dec;
    } u;
    InterCode prev;
    InterCode next;
};

struct ArgNode_ {
    Operand op;
    ArgNode next;
};

struct ArgAddr_ {
    char name[32];
    ArgAddr next;
};

int variableIndex;
int tempvarIndex;
int labelIndex;

InterCode interCodeHead;
InterCode interCodeTail;
ArgAddr argAddrList;

int calcSize(Type type);
Operand newOperand(int kind, ...);
InterCode newInterCode(int kind, ...);
void insertCode(InterCode code);
//char* oppositeRelop(char* relop);

#endif