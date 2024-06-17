#include "semantic.h"

int semanticErrorCnt = 0;

void printErrorMsg(int errorType_, int lineno, char* msg) {
    semanticErrorCnt++;
    switch (errorType_) {
        case 1:
            printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", lineno, msg);
            break;
        case 2:
            printf("Error type 2 at Line %d: Undefined function \"%s\".\n", lineno, msg);
            break;
        case 3:
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", lineno, msg);
            break;
        case 4:
            printf("Error type 4 at Line %d: Redefined function \"%s\".\n", lineno, msg);
            break;
        case 5:
            printf("Error type 5 at Line %d: Type mismatched for assignment.\n", lineno);
            break;
        case 6:
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", lineno);
            break;
        case 7:
            printf("Error type 7 at Line %d: Type mismatched for operands.\n", lineno);
            break;
        case 8:
            printf("Error type 8 at Line %d: Type mismatched for return.\n", lineno);
            break;
        case 9:
            printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments.\n", lineno, msg);
            break;
        case 10:
            printf("Error type 10 at Line %d: \"%s\" is not an array.\n", lineno, msg);
            break;
        case 11:
            printf("Error type 11 at Line %d: \"%s\" is not a function.\n", lineno, msg);
            break;
        case 12:
            printf("Error type 12 at Line %d: \"%s\" is not an integer.\n", lineno, msg);
            break;
        case 13:
            printf("Error type 13 at Line %d: Illegal use of \".\".\n", lineno);
            break;
        case 14:
            printf("Error type 14 at Line %d: Non-existent field \"%s\".\n", lineno, msg);
            break;
        case 15:
            printf("Error type 15 at Line %d: Redefined field \"%s\".\n", lineno, msg);
            break;
        case 16:
            printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", lineno, msg);
            break;
        case 17:
            printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", lineno, msg);
            break;
        default:
            printf("Unknown error at Line %d\n", lineno);
            break;
    }

}

int semanticCheck(Node* root_) {
    SymbolTable = createSymbolTable();
    Symbol read = newSymbol("read", funcType(basicType(BASIC_INT), NULL), 0);
    Symbol write = newSymbol("write", funcType(basicType(BASIC_INT),
        newField(" ", basicType(BASIC_INT), 0)), 0);
    insertSymbol(read, SymbolTable);
    insertSymbol(write, SymbolTable);
    Program(treeRoot);
    //printTable(SymbolTable);
    return semanticErrorCnt == 0;
}

// High-level Definitions
void Program(Node* cur) {
    //printf("Program\n");
    // Program → ExtDefList
    ExtDefList(getChild(cur, 1));
}

void ExtDefList(Node* cur) {
    //printf("ExtDefList\n");
    // ExtDefList → ExtDef ExtDefList
    if (cur->child != NULL) {
        ExtDef(getChild(cur, 1));
        ExtDefList(getChild(cur, 2));
    }
    // ExtDefList → sigma (do nothing)
}

void ExtDef(Node* cur) {
    //printf("ExtDef\n");
    Node* p = getChild(cur, 1);
    Type speciType = Specifier(p);
    if (speciType->kind != ERROR) {
        Node* q = getChild(cur, 2);
        // ExtDef → Specifier ExtDecList SEMI
        if (strcmp(q->name, "ExtDecList") == 0)
            ExtDecList(q, speciType);
        // ExtDef → Specifier SEMI
        else if (strcmp(q->name, "SEMI") == 0);
        // ExtDef → Specifier FunDec Compst
        else if (strcmp(q->name, "FunDec") == 0) {
            FunDec(q, speciType);
            CompSt(getChild(cur, 3), speciType);
        }
    }
}

void ExtDecList(Node* cur, Type extDecType) {
    //printf("ExtDecList\n");
    // ExtDecList → VarDec
    Symbol sym = VarDec(getChild(cur, 1), extDecType);
    // ExtDecList → VarDec COMMA ExtDecList
    if (getChild(cur, 2) != NULL)
        ExtDecList(getChild(cur, 3), extDecType);
}

// Specifiers
Type Specifier(Node* cur) {
    //printf("Specifier\n");
    Node* p = getChild(cur, 1);
    // Specifier → TYPE
    if (strcmp(p->name, "TYPE") == 0) {
        if (strcmp(p->val, "int") == 0)
            return basicType(BASIC_INT);
        else if (strcmp(p->val, "float") == 0)
            return basicType(BASIC_FLOAT);
    }
    // Specifier → StructSpecifier
    else if (strcmp(p->name, "StructSpecifier") == 0)
        return StructSpecifier(p);
}

Type StructSpecifier(Node* cur) {
    //printf("StructSpecifier\n");
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "STRUCT") == 0) {
        Node* q = getChild(cur, 2);
        // StructSpecifier → STRUCT OptTag LC DefList RC
        if (strcmp(q->name, "OptTag") == 0) {
            char* optTagName = OptTag(q);
            if ((strcmp(optTagName, "123") == 0))
                return errorType(16);
            Node* d = getChild(cur, 4);
            FieldList defList = StructDefList(d);
            FieldList pF = defList;
            while (pF != NULL) {
                if (pF->type->kind == ERROR)
                    return pF->type;
                FieldList qF = pF->tail;
                while (qF != NULL) {
                    if (strcmp(pF->name, qF->name) == 0) {
                        printErrorMsg(15, qF->defineLine, qF->name);
                        return errorType(15);
                    }
                    qF = qF->tail;
                }
                pF = pF->tail;
            }
            Type structT = structType(defList);
            Symbol newSym = newSymbol(optTagName, structT, q->line);
            insertSymbol(newSym, SymbolTable);
            return structT;
        } 
        // Struct Specifier → STRUCT Tag
        else if (strcmp(q->name, "Tag") == 0)
            return Tag(q);
    }
}

char* OptTag(Node* cur) {
    char* doNotInsert = "123";
    //printf("OptTag\n");
    // OptTag → ID
    if (cur->child != NULL) {
        Node* p = getChild(cur, 1);
        Symbol symbol = lookUpTable(p->val, SymbolTable);
        if (symbol != NULL) {
            printErrorMsg(16, p->line, p->val);
            return doNotInsert;
        }
        else
            return p->val;
    }
    // OptTag → sigma (return nothing)
    return doNotInsert;
}

Type Tag(Node* cur) {
    //printf("Tag\n");
    Node* p = getChild(cur, 1);
    //printTable(SymbolTable);
    // Tag → ID
    Symbol symbol = lookUpTable(p->val, SymbolTable);
    if (symbol == NULL) {
        printErrorMsg(17, p->line, p->val);
        return errorType(17);
    }
    else
        return symbol->type;
}

// Declarators
Symbol VarDec(Node* cur, Type varDecType) {
    //printf("VarDec\n");
    Node* p = getChild(cur, 1);
    // VarDec → ID
    if (strcmp(p->name, "ID") == 0) {
        if (lookUpTable(p->val, SymbolTable) != NULL) {
            printErrorMsg(3, p->line, p->val);
            return newSymbol(" ", errorType(13), p->line);
        }
        else {
            if (getChild(cur, 2) != NULL) {
                Type t = Exp(getChild(cur, 3));
                if (equalType(t, varDecType) == 0)
                    return newSymbol(" ", errorType(5), p->line);
            }
            Symbol symbol = newSymbol(p->val, varDecType, p->line);
            insertSymbol(symbol, SymbolTable);
            return symbol;
        }

    }
    // VarDec → VarDec LB INT RB
    else if (strcmp(p->name, "VarDec") == 0) {
        Symbol varDec = VarDec(p, varDecType);
        if (varDec->type->kind != ERROR) {
            Type arrayT = varDec->type;
            Node* intN = getChild(cur, 3);
            int arrayS = (int)(atoi(intN->val));
            Type newArrayT = arrayType(arrayT, arrayS);
            varDec->type = newArrayT;
        }
        return varDec;
    }
}

Symbol StructVarDec(Node* cur, Type varDecType) {
    //printf("VarDec\n");
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "ID") == 0) {
        Symbol symbol = newSymbol(p->val, varDecType, p->line);
        if (lookUpTable(p->val, SymbolTable) == NULL)
            insertSymbol(symbol, SymbolTable);
        return symbol;
    }
    else if (strcmp(p->name, "VarDec") == 0) {
        Symbol varDec = StructVarDec(p, varDecType);
        if (varDec->type->kind != ERROR) {
            Type arrayT = varDec->type;
            Node* intN = getChild(cur, 3);
            int arrayS = (int)(atoi(intN->val));
            Type newArrayT = arrayType(arrayT, arrayS);
            varDec->type = newArrayT;
        }
        return varDec;
    }
}

void FunDec(Node* cur, Type funDecType) {
    //printf("FunDec\n");
    Node* p = getChild(cur, 1);
    Symbol idSym = lookUpTable(p->val, SymbolTable);
    if (idSym != NULL)
        printErrorMsg(4, p->line, p->val);
    else {
        FieldList varList = NULL;
        // FunDec → ID LP VarList RP
        if (getChild(cur, 4) != NULL) {
            Node* q = getChild(cur, 3);
            varList = VarList(q);
            FieldList temp = varList;
            while (temp != NULL) {
                if (temp->type->kind == ERROR)
                    return;
                temp = temp->tail;
            }
        }
        // FunDec → ID LP RP (no var list)
        Type funcT = funcType(funDecType, varList);
        Symbol newSym = newSymbol(p->val, funcT, p->line);
        insertSymbol(newSym, SymbolTable);
    }
}

FieldList VarList(Node* cur) {
    //printf("VarList\n");
    Node* p = getChild(cur, 1);
    FieldList head = ParamDec(p);
    Node* q = getChild(cur, 2);
    // VarList → ParamDec COMMA VarList
    if (q != NULL) {
        FieldList tail = VarList(getChild(cur, 3));
        head->tail = tail;
    }
    // VarList → ParamDec
    return head;
}

FieldList ParamDec(Node* cur) {
    //printf("ParamDec\n");
    // ParamDec → Specifier VarDec
    Node* p = getChild(cur, 1);
    Type paramType = Specifier(p);
    if (paramType->kind != ERROR) {
        Node* q = getChild(cur, 2);
        Symbol temp = VarDec(q, paramType);
        if (temp->type->kind == ERROR)
            return newField(" ", errorType(12), q->line);
        else {
            FieldList param = newField(temp->name, temp->type, q->line);
            paramType = param->type;
            Symbol paramSym = newSymbol(param->name, paramType, q->line);
            insertSymbol(paramSym, SymbolTable);
            return param;
        }
    }
    else
        return newField(" ", paramType, p->line);
}

// Statements
void CompSt(Node* cur, Type compStType) {
    //printf("CompSt\n");
    // CompSt → LC DefList StmtList RC
    Node* p = getChild(cur, 2);
    Node* q = getChild(cur, 3);
    if (strcmp(p->name, "DefList") == 0)
        DefList(p);
    if (strcmp(q->name, "StmtList") == 0)
        StmtList(q, compStType);
}

void StmtList(Node* cur, Type stmtType) {
    //printf("StmtList\n");
    // StmtList → Stmt StmtList
    if (cur->child != NULL) {
        Stmt(getChild(cur, 1), stmtType);
        StmtList(getChild(cur, 2), stmtType);
    }
    // StmtList → sigma (do nothing)
}

void Stmt(Node* cur, Type stmtType) {
    //printf("Stmt\n");
    Node* p = getChild(cur, 1);
    // Stmt → Exp SEMI
    if (strcmp(p->name, "Exp") == 0)
        Exp(p);
    // Stmt → CompSt
    else if (strcmp(p->name, "CompSt") == 0)
        CompSt(p, stmtType);
    // Stmt → RETURN Exp SEMI
    else if (strcmp(p->name, "RETURN") == 0) {
        Type returnType = Exp(getChild(cur, 2));
        if (returnType->kind != ERROR) {
            if (equalType(returnType, stmtType) == 0) {
                printErrorMsg(8, p->line, "");
            }
        }
    }
    else if (strcmp(p->name, "IF") == 0) {
        Type t = Exp(getChild(cur, 3));
        // Stmt → IF LP Exp RP Stmt
        Stmt(getChild(cur, 5), stmtType);
        // Stmt → IF LP Exp RP Stmt ELSE Stmt
        if (getChild(cur, 6) != NULL)
            Stmt(getChild(cur, 7), stmtType);
    }
    // Stmt → WHILE LP Exp RP Stmt
    else if (strcmp(p->name, "WHILE") == 0) {
        Type t = Exp(getChild(cur, 3));
        Stmt(getChild(cur, 5), stmtType);
    }
}

// Local Definitions
void DefList(Node* cur) {
    //printf("DefList\n");
    // DefList → Def DefList
    if (cur->child != NULL) {
        Def(getChild(cur, 1));
        DefList(getChild(cur, 2));
    }
    // DefList → sigma (do nothing)
}

FieldList StructDefList(Node* cur) {
    //printf("DefList\n");
    if (cur->child != NULL) {
        FieldList head = StructDef(getChild(cur, 1));
        FieldList tail = StructDefList(getChild(cur, 2));
        head->tail = tail;
        return head;
    }
    return NULL;
}

void Def(Node* cur) {
    //printf("Def\n");
    // Def → Specifier DecList SEMI
    Type defType = Specifier(getChild(cur, 1));
    if (defType->kind != ERROR)
        DecList(getChild(cur, 2), defType);
}

FieldList StructDef (Node* cur) {
    //printf("Def\n");
    Node* p = getChild(cur, 1);
    Type defType = Specifier(p);
    if (defType->kind != ERROR)
        return StructDecList(getChild(cur, 2), defType);
    return newField(" ", defType, p->line);
}

void DecList(Node* cur, Type decType) {
    //printf("DecList\n");
    // DecList → Dec
    Dec(getChild(cur, 1), decType);
    // DecList →  Dec COMMA DecList
    if (getChild(cur, 2) != NULL)
        DecList(getChild(cur, 3), decType);
}

FieldList StructDecList(Node* cur, Type decType) {
    //printf("DecList\n");
    FieldList head = StructDec(getChild(cur, 1), decType);
    if (getChild(cur, 2) != NULL) {
        FieldList tail = StructDecList(getChild(cur, 3), decType);
        head->tail = tail;
    }
    return head;
}

void Dec(Node* cur, Type decType) {
    //printf("Dec\n");
    // Dec → VarDec
    Symbol newDec = VarDec(getChild(cur, 1), decType);
    if (newDec->type->kind == ERROR)
        return;
    Node* p = getChild(cur, 2);
    // Dec → VarDec ASSIGNOP Exp
    if (p != NULL) {
        Type expType = Exp(getChild(cur, 3));
        if (expType->kind != ERROR) {
            if (equalType(newDec->type, expType) == 0)
                printErrorMsg(5, p->line, "");
        }
    }
}

FieldList StructDec(Node* cur, Type decType) {
    //printf("Dec\n");
    Node* p = getChild(cur, 1);
    Symbol newDec = StructVarDec(p, decType);
    if (newDec->type->kind == ERROR)
        return newField(" ", newDec->type, cur->line);
    Node* q = getChild(cur, 2);
    if (q != NULL) {
        Type expType = Exp(getChild(cur, 3));
        if (expType->kind != ERROR) {
            if (equalType(newDec->type, expType) == 0) {
                printErrorMsg(5, q->line, "");
                return newField(" ", errorType(5), q->line);
            }
        }
    }
    return newField(newDec->name, newDec->type, newDec->defineLine);
}

// Expressions
Type Exp(Node* cur) {
    //printf("Exp\n");
    Node* p = getChild(cur, 1);
    if (strcmp(p->name, "Exp") == 0) {
        Node* q = getChild(cur, 2);
        // Exp → Exp ASSIGNOP Exp
        if (strcmp(q->name, "ASSIGNOP") == 0) {
            Node* r = getChild(cur, 3);
            Type pT = Exp(p);
            Type rT = Exp(r);
            if (pT->kind == ERROR)
                return pT;
            if (rT->kind == ERROR)
                return rT;
            if (getChild(p, 1)->type == INT_ || getChild(p, 1)->type == FLOAT_) {
                printErrorMsg(6, p->line, "");
                return errorType(6);
            }
            if (equalType(pT, rT) == 0) {
                printErrorMsg(5, p->line, "");
                return errorType(5);
            }
        }
        // Exp → Exp AND Exp
        // Exp → Exp OR Exp
        else if (strcmp(q->name, "AND") == 0 || strcmp(q->name, "OR") == 0) {
            Node* r = getChild(cur, 3);
            Type pT = Exp(p);
            Type rT = Exp(r);
            if (pT->kind == ERROR)
                return pT;
            if (rT->kind == ERROR)
                return rT; 
            if (isInt(pT) == 0) {
                printErrorMsg(7, p->line, "");
                return errorType(7);
            }
            else if (isInt(Exp(r)) == 0) {
                printErrorMsg(7, r->line, "");
                return errorType(7);
            }    
            else
                return basicType(BASIC_INT);
        }
        // Exp → Exp RELOP EXp (PLUS, MINUS, STAR, DEV)
        else if (strcmp(q->name, "RELOP") == 0 || strcmp(q->name, "PLUS") == 0
            || strcmp(q->name, "MINUS") == 0 || strcmp(q->name, "STAR") == 0
            || strcmp(q->name, "DIV") == 0) {
            Node* r = getChild(cur, 3);
            Type pT = Exp(p);
            Type rT = Exp(r);
            if (pT->kind == ERROR)
                return pT;
            if (rT->kind == ERROR)
                return rT; 
            if (pT->kind != BASIC) {
                printErrorMsg(7, p->line, "");
                return errorType(7);
            }
            else if (equalType(pT, rT) == 0) {
                printErrorMsg(7, r->line, "");
                return errorType(7);
            }
            else {
                if (strcmp(q->name, "RELOP") == 0)
                    return basicType(BASIC_INT);
                else
                    return pT;
            }
        }
        // Exp → Exp LB Exp RB
        else if (strcmp(q->name, "LB") == 0) {
            Type pT = Exp(p);
            if (pT->kind == ERROR)
                return pT;
            if (pT->kind != ARRAY) {
                printErrorMsg(10, p->line, getChild(p, 1)->val);
                return errorType(10);
            }
            else {
                Node* r = getChild(cur, 3);
                if (isInt(Exp(r)) == 0) {
                    Node* c = getChild(r, 1);
                    printErrorMsg(12, c->line, c->val);
                    return errorType(12);
                }
                else
                    return pT->u.array.elem;
            }
        }
        // Exp → Exp DOT ID
        else if (strcmp(q->name, "DOT") == 0) {
            Type pT = Exp(p);
            if (pT->kind == ERROR)
                return pT;
            if (pT->kind == STRUCTURE) {
                Node* r = getChild(cur, 3);
                FieldList l = pT->u.structure;
                while (l != NULL && strcmp(l->name, r->val) != 0)
                    l = l->tail;
                if (l == NULL) {
                    printErrorMsg(14, p->line, r->val);
                    return errorType(14);
                }
                else
                    return l->type;
            }
            else {
                printErrorMsg(13, p->line, "");
                return errorType(13);
            }
        }
    }
    // Exp → LP Exp RP
    else if (strcmp(p->name, "LP") == 0) {
        Node* q = getChild(cur, 2);
        return Exp(q);
    }
    // Exp → MINUS Exp
    else if (strcmp(p->name, "MINUS") == 0) {
        Node* q = getChild(cur, 2);
        Type qT = Exp(q);
        if (qT->kind == ERROR)
            return qT;
        if (qT->kind != BASIC) {
            printErrorMsg(7, q->line, "");
            return errorType(7);
        }
        else
            return qT;
    }
    // Exp → NOT Exp
    else if (strcmp(p->name, "NOT") == 0) {
        Node* q = getChild(cur, 2);
        Type qT = Exp(q);
        if (qT->kind == ERROR)
            return qT;
        if (isInt(qT) == 0) {
            printErrorMsg(7, q->line, "");
            return errorType(7);
        }
        else
            return qT;    
    }
    else if (strcmp(p->name, "ID") == 0) {
        Node* q = getChild(cur, 2);
        // Exp → ID
        if (q == NULL) {
            Symbol idSym = lookUpTable(p->val, SymbolTable);
            if (idSym == NULL) {
                printErrorMsg(1, p->line, p->val);
                return errorType(1);
            }
            else
                return idSym->type;
        }
        else {
            Node* r = getChild(cur, 3);
            Symbol funcSym = lookUpTable(p->val, SymbolTable);
            if (funcSym == NULL) {
                printErrorMsg(2, p->line, p->val);
                return errorType(2);
            }
            else if (funcSym->type->kind != FUNCTION) {
                printErrorMsg(11, p->line, p->val);
                return errorType(11);
            }
            else {
                // Exp → ID LP Args RP
                if (strcmp(r->name, "Args") == 0) {
                    int i = 0;
                    FieldList parameters = funcSym->type->u.function.parameters;
                    FieldList arguments = Args(r);
                    if (strcmp(p->val, "write") == 0 || equalList(parameters, arguments))
                        return funcSym->type->u.function.returnType;
                    else {
                        printErrorMsg(9, p->line, p->val);
                        return errorType(9);
                    }
                }
                // Exp → ID LP RP
                else {
                    if (funcSym->type->u.function.parameters == NULL)
                        return funcSym->type->u.function.returnType;
                    else {
                        printErrorMsg(9, p->line, p->val);
                        return errorType(9);
                    }
                }
            }
        }
    }
    // Exp → INT
    else if (strcmp(p->name, "INT") == 0)
        return basicType(BASIC_INT);
    // Exp → FLOAT
    else if (strcmp(p->name, "FLOAT") == 0)
        return basicType(BASIC_FLOAT);
}

FieldList Args(Node* cur) {
    //printf("Args\n");
    Node* p = getChild(cur, 1);
    // Args → Exp COMMA Args
    if (getChild(cur, 2) != NULL) {
        FieldList head = newField("", Exp(p), p->line);
        FieldList tail = Args(getChild(cur, 3));
        head->tail = tail;
        return head;
    }
    // Args → Exp
    else {
        return newField("", Exp(p), p->line);
    }
}