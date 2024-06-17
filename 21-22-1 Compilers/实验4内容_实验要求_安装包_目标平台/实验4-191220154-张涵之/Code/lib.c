#include "lib.h"

Node* createNode(char n[], char v[], int l, _Type t) {
	Node* temp = (Node*)malloc(sizeof(Node));
	strcpy(temp->name, n);
	switch (t) {
		case INT_: 
		case FLOAT_:
		case ID_:
		case TYPE_:
        case RELOP_:
			strcpy(temp->val, v);
			break;
		default:
			break;
	}
	temp->line = l;
	temp->type = t;
	temp->child = NULL;
	temp->next = NULL;
	return temp;
}

void modifyTree(Node* cur, int cnt, ...) {
	va_list l;
	va_start(l, cnt);
	Node* temp = va_arg(l, Node*);
	cur->child = temp;
	for (int i = 1; i < cnt; i++) {
		temp->next = va_arg(l, Node*);
		if (temp->next != NULL)
			temp = temp->next;
	}
}

void printNode(Node* cur) {
	switch(cur->type) {
		case(INT_):
		case(FLOAT_):
		case(ID_):
		case(TYPE_):
			printf("%s: %s\n", cur->name, cur->val);
			break;
		case(COMPLEX_):
			printf("%s (%d)\n", cur->name, cur->line);
			break;			
		default:
			printf("%s\n", cur->name);
			break;
	}
}

void printTree(Node* root, int depth) {
	if (root != NULL) {
		for (int i = 0; i < depth; i++)
			printf("  ");
		printNode(root);
		printTree(root->child, depth + 1);
		printTree(root->next, depth);
	}
}

Node* getChild(Node* cur, int cnt) {
    Node* p = cur->child;
    for (int i = 1; i < cnt; i++) {
        if (p == NULL)
            break;
        p = p->next;
    }
    return p;
}


unsigned int hash_pjw(char* name, int size) {
    unsigned int val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if (i = val & ~size) val = (val ^ (i >> 12)) & size;
    }
    return val;
}

FieldList* creatFieldList() {
    FieldList* list = (FieldList*)malloc(FIELDLIST_SIZE * sizeof(FieldList));
    for (int i = 0; i < FIELDLIST_SIZE; i++)
        list[i] = NULL;
    return list;
}

Symbol* createSymbolTable() {
    Symbol* table = (Symbol*)malloc(SYMTABLE_SIZE * sizeof(Symbol));
    for (int i = 0; i < SYMTABLE_SIZE; i++)
        table[i] = NULL;
    return table;
}

Type basicType(int basic_) {
    Type bt = (Type)malloc(sizeof(struct Type_));
    bt->kind = BASIC;
    bt->u.basic = basic_;
    return bt;
}

Type arrayType(Type elem_, int size_) {
    Type at = (Type)malloc(sizeof(struct Type_));
    at->kind = ARRAY;
    at->u.array.elem = elem_;
    at->u.array.size = size_;
    return at;
}

Type structType(FieldList members_) {
    Type st = (Type)malloc(sizeof(struct Type_));
    st->kind = STRUCTURE;
    st->u.structure = members_;
    return st;
}

Type funcType(Type returnType_, FieldList parameters_) {
    Type ft = (Type)malloc(sizeof(struct Type_));
    ft->kind = FUNCTION;
    ft->u.function.returnType = returnType_;
    ft->u.function.parameters = parameters_;
    return ft;
}

Type errorType(int errorCode_) {
    Type et = (Type)malloc(sizeof(struct Type_));
    et->kind = ERROR;
    et->u.errorCode = errorCode_;
    return et;
}

int isInt(Type t) {
    if (t->kind == BASIC && t->u.basic == BASIC_INT)
        return 1;
    else
        return 0;
}

int isFloat(Type t) {
    if (t->kind == BASIC && t->u.basic == BASIC_FLOAT)
        return 1;
    else
        return 0;
}

FieldList newField(char* name_, Type type_, int line_) {
    FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
    strcpy(f->name, name_);
    f->type = type_;
    f->defineLine = line_;
    f->tail = NULL;
    return f;
}

Symbol newSymbol(char* name_, Type type_, int line_) {
    Symbol s = (Symbol)malloc(sizeof(struct Symbol_));
    strcpy(s->name, name_);
    s->type = type_;
    s->varIndex = -1;
    s->defineLine = line_;
    s->hashTail = NULL;
    return s;
}

int equalList(FieldList l1, FieldList l2) {
    if (l1 == NULL && l2 == NULL)
        return 1;
    else if (l1 == NULL || l2 == NULL)
        return 0;
    else
        return equalType(l1->type, l2->type) && equalList(l1->tail, l2->tail);
}

int equalType(Type t1, Type t2) {
    if (t1->kind != t2->kind)
        return 0;
    else {
        switch (t1->kind) {
            case(BASIC):
                return t1->u.basic == t2->u.basic;
            case(ARRAY):
                return equalType(t1->u.array.elem, t2->u.array.elem);
            case(STRUCTURE):
                return equalList(t1->u.structure, t2->u.structure);
            case(FUNCTION):
                return equalType(t1->u.function.returnType, t2->u.function.returnType)
                    && equalList(t1->u.function.parameters, t2->u.function.parameters);
            default:
                return 0;
        }
    }
    return 0;
}

void insertSymbol(Symbol symbol_, Symbol* table_) {
    unsigned int i = hash_pjw(symbol_->name, SYMTABLE_SIZE);
    if (table_[i] == NULL)
        table_[i] = symbol_;
    else {
        Symbol cur = table_[i];
        while (cur->hashTail != NULL)
            cur = cur->hashTail;
        cur->hashTail = symbol_;
    }
}

Symbol lookUpTable(char* name_, Symbol* table_) {
    unsigned int i = hash_pjw(name_, SYMTABLE_SIZE);
    if (table_[i] == NULL)
        return NULL;
    else {
        Symbol cur = table_[i];
        while (cur != NULL) {
            if (strcmp(cur->name, name_) == 0)
                return cur;
            cur = cur->hashTail;
        }
    }
    return NULL;
}

void freeSymbol(Symbol cur) {
    if (cur != NULL) {
        freeSymbol(cur->hashTail);
        free(cur);
    }
}

void delTable(Symbol* table_) {
    for (int i = 0; i < SYMTABLE_SIZE; i++)
        freeSymbol(table_[i]);
    free(table_);
}

void printTable(Symbol* table_) {
    for(int i = 0; i < SYMTABLE_SIZE; i++) {
        Symbol p = table_[i];
        while (p != NULL) {
            printf("  \"%s, %d\"\n", p->name, i);
            p = p->hashTail;
        }
    }
}

int calcSize(Type type) {
    if (type->kind == BASIC)
        return 4;
    else if (type->kind == ARRAY)
        return type->u.array.size * calcSize(type->u.array.elem);
    else
        return -1;
}

Operand newOperand(int kind, ...) {
    va_list args;
    va_start(args, kind);
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = kind;
    char tempName[32];
    int tempI;
    switch (kind) {
        case CONSTANT:
            op->u.var = va_arg(args, int);
            break;
        case TEMPVAR:
            tempI = tempvarIndex++;
            sprintf(tempName, "t%d", tempI);
            strcpy(op->u.value, tempName);
            break;
        case LABEL:
            tempI = labelIndex++;
            sprintf(tempName, "label%d", tempI);
            strcpy(op->u.value, tempName);
            break;
        case VARIABLE:
        case ADDRESS:
        case POINTER:
        case FUNC:
            strcpy(op->u.value, va_arg(args, char*));
            break;
        case OTHER:
            strcpy(op->u.value, " ");
            break;
        default:
            break;
    }
    va_end(args);
    return op;
}

InterCode newInterCode(int kind, ...) {
    va_list args;
    va_start(args, kind);
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->kind = kind;
    code->prev = NULL;
    code->next = NULL;
    switch (kind) {
        case _ASSIGN:
        case _CALL:
            code->u.assign.left = va_arg(args, Operand);
            code->u.assign.right = va_arg(args, Operand);
            break;
        case _LABEL:
        case _FUNC:
        case _GOTO:
        case _RETURN:
        case _ARG:
        case _PARAM:
        case _READ:
        case _WRITE:
            code->u.sinop.op = va_arg(args, Operand);
            break;
        case _ADD:
        case _SUB:
        case _MUL:
        case _DIV:
            code->u.binop.result = va_arg(args, Operand);
            code->u.binop.op1 = va_arg(args, Operand);
            code->u.binop.op2 = va_arg(args, Operand);
            break;
        case _IFGOTO:
            code->u.ifgoto.x = va_arg(args, Operand);
            code->u.ifgoto.y = va_arg(args, Operand);
            code->u.ifgoto.z = va_arg(args, Operand);
            strcpy(code->u.ifgoto.relop, va_arg(args, char*));
            break;
        case _DEC:
            code->u.dec.op = va_arg(args, Operand);
            code->u.dec.size = va_arg(args, int);
            break;
        default:
            break; 
    }
    va_end(args);
    return code;
}

void insertCode(InterCode code) {
    if (interCodeHead == NULL) {
        interCodeHead = code;
        interCodeTail = code;
    }
    else {
        interCodeTail->next = code;
        code->prev = interCodeTail;
        interCodeTail = interCodeTail->next;
    }
}

/*char* oppositeRelop(char* relop) {
    if (strcmp(relop, ">") == 0)
        return "<=";
    else if (strcmp(relop, "<") == 0)
        return ">=";
    else if (strcmp(relop, ">=") == 0)
        return "<";
    else if (strcmp(relop, "<=") == 0)
        return ">";
    else if (strcmp(relop, "==") == 0)
        return "!=";
    else if (strcmp(relop, "!=") == 0)
        return "==";
    return "";
}*/

void initMemoryBlock() {
    MemoryBlock = (Memory*)malloc(MEMORY_SIZE * sizeof(Memory));
    for (int i = 0; i < MEMORY_SIZE; i++)
        MemoryBlock[i] = NULL;
}

Memory newMemory(char* name, int fpOffset) {
    Memory newMem = (Memory)malloc(sizeof(struct Memory_));
    strcpy(newMem->name, name);
    newMem->fpOffset = fpOffset;
    newMem->link = NULL;
    return newMem;
}

void insertMemory(Memory mem) {
    unsigned int i = hash_pjw(mem->name, MEMORY_SIZE);
    if (MemoryBlock[i] == NULL)
        MemoryBlock[i] = mem;
    else {
        Memory cur = MemoryBlock[i];
        while (cur->link != NULL)
            cur = cur->link;
        cur->link = mem;
    }
}

Memory lookUpBlock(char* name) {
    unsigned int i = hash_pjw(name, MEMORY_SIZE);
    if (MemoryBlock[i] == NULL)
        return NULL;
    else {
        Memory cur = MemoryBlock[i];
        while (cur != NULL) {
            if (strcmp(cur->name, name) == 0)
                return cur;
            cur = cur->link;
        }
    }
    return NULL;
}

char* findFreeTReg() {
    for (int i = 0; i < 10; i++) {
        if (FreeTReg[i] == 1) {
            FreeTReg[i] = 0;
            char* freeTRegName;
            freeTRegName = (char*)malloc(sizeof(char) * 32);
            sprintf(freeTRegName, "$t%d", i);
            return freeTRegName;
        }
    }
    return " ";
}

void freeAllTReg() {
    for (int i = 0; i < 10; i++)
        FreeTReg[i] = 1;
}

char* findLeftReg(FILE *p, Operand op) {
    char* TRegName = findFreeTReg();
    switch (op->kind) {
        case VARIABLE:
        case TEMPVAR:
            if (lookUpBlock(op->u.value) == NULL) {
                fprintf(p, "  addi $sp, $sp, -4\n");
                stack_sp = stack_sp - 4;
                Memory mem = newMemory(op->u.value, stack_sp - stack_fp);
                insertMemory(mem);
            }
            break;
        case POINTER:
            genAssemblyCode(p, LW_, TRegName, lookUpBlock(op->u.value)->fpOffset, "$fp");
        break;
    }
    return TRegName;
}

char* findRightReg(FILE *p, Operand op) {
    char* TRegName = findFreeTReg();
    if (op->kind != CONSTANT) {
        int fpOffset = lookUpBlock(op->u.value)->fpOffset;
        switch (op->kind) {
            case VARIABLE:
            case TEMPVAR:
                genAssemblyCode(p, LW_, TRegName, fpOffset, "$fp");
                break;
            case ADDRESS:
                genAssemblyCode(p, ADDI_, TRegName, "$fp", fpOffset);
                break;
            case POINTER:
                genAssemblyCode(p, LW_, TRegName, fpOffset, "$fp");
                genAssemblyCode(p, LW_, TRegName, 0, TRegName);
                break;
            default:
                break;
        }
    }
    return TRegName;
}

void genAssemblyCode(FILE *p, COMMAND_ c, ...) {
    va_list args;
    va_start(args, c);
    char* reg1;
    char* reg2;
    char* reg3;
    int arg;
    switch (c) {
        case LI_:
            //printf("li\n");
            reg1 = va_arg(args, char*);
            arg = va_arg(args, int);
            fprintf(p, "  li %s, %d\n", reg1, arg);
            break;
        case MOVE_:
            //printf("move\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  move %s, %s\n", reg1, reg2);
            break;
        case ADDI_:
            //printf("addi\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            arg = va_arg(args, int);
            fprintf(p, "  addi %s, %s, %d\n", reg1, reg2, arg);
            break;
        case ADD_:
            //printf("add\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            reg3 = va_arg(args, char*);
            fprintf(p, "  add %s, %s, %s\n", reg1, reg2, reg3);
            break;
        case SUB_:
            //printf("sub\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            reg3 = va_arg(args, char*);
            fprintf(p, "  sub %s, %s, %s\n", reg1, reg2, reg3);
            break;
        case MUL_:
            //printf("mul\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            reg3 = va_arg(args, char*);
            fprintf(p, "  mul %s, %s, %s\n", reg1, reg2, reg3);
            break;
        case DIV__:
            //printf("div\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            reg3 = va_arg(args, char*);
            fprintf(p, "  div %s, %s\n", reg1, reg2);
            fprintf(p, "  mflo %s\n", reg3);
            break;
        case LW_:
            //printf("lw\n");
            reg1 = va_arg(args, char*);
            arg = va_arg(args, int);
            reg2 = va_arg(args, char*);
            fprintf(p, "  lw %s, %d(%s)\n", reg1, arg, reg2);
            break;
        case SW_:
            //printf("sw\n");
            reg1 = va_arg(args, char*);
            arg = va_arg(args, int);
            reg2 = va_arg(args, char*);
            fprintf(p, "  sw %s, %d(%s)\n", reg1, arg, reg2);
            break;
        case BEQ_:
            //printf("beq\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  beq %s, %s ", reg1, reg2);
            break;
        case BNE_:
            //printf("bne\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  bne %s, %s ", reg1, reg2);
            break;
        case BGT_:
            //printf("bgt\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  bgt %s, %s ", reg1, reg2);
            break;
        case BLT_:
            //printf("blt\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  blt %s, %s ", reg1, reg2);
            break;
        case BGE_:
            //printf("bge\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  bge %s, %s ", reg1, reg2);
            break;
        case BLE_:
            //printf("ble\n");
            reg1 = va_arg(args, char*);
            reg2 = va_arg(args, char*);
            fprintf(p, "  ble %s, %s ", reg1, reg2);
            break;
        default:
            break;
    }
    va_end(args);
}