%{
	#include "lib.h"

	int yylex();
	int yyerror(const char* msg, ...);
	int yylineno;

	int syntaxErrorCnt = 0;
%}

/* declared types */
%union {
	Node* type_node;
}

%locations
%define parse.error verbose
/* declared tokens */
%token <type_node> INT
%token <type_node> FLOAT
%token <type_node> ID
%token <type_node> SEMI
%token <type_node> COMMA
%token <type_node> ASSIGNOP
%token <type_node> RELOP
%token <type_node> PLUS
%token <type_node> MINUS
%token <type_node> STAR
%token <type_node> DIV
%token <type_node> AND
%token <type_node> OR
%token <type_node> DOT
%token <type_node> NOT
%token <type_node> TYPE
%token <type_node> LP
%token <type_node> RP
%token <type_node> LB
%token <type_node> RB
%token <type_node> LC
%token <type_node> RC
%token <type_node> STRUCT
%token <type_node> RETURN
%token <type_node> IF
%token <type_node> ELSE
%token <type_node> WHILE

/* declared high-level definitions */
%type <type_node> Program
%type <type_node> ExtDefList
%type <type_node> ExtDef
%type <type_node> ExtDecList

/* declared specifiers */
%type <type_node> Specifier
%type <type_node> StructSpecifier
%type <type_node> OptTag
%type <type_node> Tag

/* declared declarators */
%type <type_node> VarDec
%type <type_node> FunDec
%type <type_node> VarList
%type <type_node> ParamDec

/* declared statements */
%type <type_node> CompSt
%type <type_node> StmtList
%type <type_node> Stmt

/* declared local definitions */
%type <type_node> DefList
%type <type_node> Def
%type <type_node> DecList
%type <type_node> Dec

/* declared expressions */
%type <type_node> Exp
%type <type_node> Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left NEG
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
/* High-level Definitions*/

Program : ExtDefList {
	$$ = createNode("Program", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
	treeRoot = $$;
};

ExtDefList : ExtDef ExtDefList {
	$$ = createNode("ExtDefList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| /* empty */ {
	$$ = createNode("ExtDefList", " ", @$.first_line, COMPLEX_);;
	@$.first_line = yylineno;
};

ExtDef : Specifier ExtDecList SEMI {
	$$ = createNode("ExtDef", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Specifier SEMI {
	$$ = createNode("ExtDef", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| Specifier FunDec CompSt {
	$$ = createNode("ExtDef", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| error SEMI {
	yyerror("Wrong type");
	yyerrok;
}
| Specifier error {
	yyerror("Missing \";\"");
	yyerrok;
};

ExtDecList : VarDec {
	$$ = createNode("ExtDecList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| VarDec COMMA ExtDecList {
	$$ = createNode("ExtDecList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| VarDec error ExtDecList {
	yyerror("Missing \",\"");
	yyerrok;
};

/* Specifiers */

Specifier : TYPE {
	$$ = createNode("Specifier", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| StructSpecifier {
	$$ = createNode("Specifier", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
};

StructSpecifier : STRUCT OptTag LC DefList RC {
	$$ = createNode("StructSpecifier", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 5, $1, $2, $3, $4, $5);
}
| STRUCT Tag {
	$$ = createNode("StructSpecifier", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
};

OptTag : ID {
	$$ = createNode("OptTag", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| /* empty */ {
	$$ = createNode("OptTag", " ", @$.first_line, COMPLEX_);
};

Tag : ID {
	$$ = createNode("Tag", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
};

/* Declarators */

VarDec : ID {
	$$ = createNode("VarDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
/*| ID ASSIGNOP Exp {
	$$ = createNode("VarDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}*/
| VarDec LB INT RB {
	$$ = createNode("VarDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 4, $1, $2, $3, $4);
}
| VarDec LB error RB {
	yyerror("Wrong type");
	yyerrok;
}
| VarDec LB INT error {
	yyerror("Missing \"]\"");
};

FunDec : ID LP VarList RP {
	$$ = createNode("FunDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 4, $1, $2, $3, $4);
}
| ID LP RP {
	$$ = createNode("FunDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| ID LP error RP {
	yyerror("Invalid arguement(s)");
	yyerrok;
}
| ID LP VarList error {
	yyerror("Missing \")\"");
	yyerrok;
};

VarList : ParamDec COMMA VarList {
	$$ = createNode("VarList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| ParamDec {
	$$ = createNode("VarList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
};

ParamDec : Specifier VarDec {
	$$ = createNode("ParamDec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
};

/* Statements */

CompSt : LC DefList StmtList RC {
	$$ = createNode("CompSt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 4, $1, $2, $3, $4);
}
| LC error RC {
	yyerror("Invalid statement(s)");
	yyerrok;
};

StmtList : Stmt StmtList {
	$$ = createNode("StmtList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| /* empty */ {
	$$ = createNode("StmtList", " ", @$.first_line, COMPLEX_);
};

Stmt : Exp SEMI {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| CompSt {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| RETURN Exp SEMI {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| IF LP Exp RP Stmt {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 5, $1, $2, $3, $4, $5);
}
| IF LP Exp RP Stmt ELSE Stmt {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 7, $1, $2, $3, $4, $5, $6, $7);
}
| WHILE LP Exp RP Stmt {
	$$ = createNode("Stmt", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 5, $1, $2, $3, $4, $5);
}
| Exp error {
	yyerror("Missing \";\"");
	yyerrok;
}
| RETURN Exp error {
	yyerror("Missing \";\"");
	yyerrok;
};

/* Local Definitions */

DefList : Def DefList {
	$$ = createNode("DefList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| /* empty */ {
	$$ = createNode("DefList", " ", @$.first_line, COMPLEX_);
};

Def : Specifier DecList SEMI {
	$$ = createNode("Def", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Specifier error SEMI {
	yyerror("Wrong variable(s)");
	yyerrok;
}
| Specifier DecList error {
	yyerror("Missing \";\"");
	yyerrok;
}

DecList : Dec {
	$$ = createNode("DecList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| Dec COMMA DecList {
	$$ = createNode("DecList", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
};

Dec : VarDec {
	$$ = createNode("Dec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| VarDec ASSIGNOP Exp {
	$$ = createNode("Dec", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| VarDec ASSIGNOP error {
	yyerror("Invalid expression");
	yyerrok;
};

Exp : Exp ASSIGNOP Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp AND Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp OR Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp RELOP Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp PLUS Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp MINUS Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp STAR Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp DIV Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| LP Exp RP {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| MINUS Exp %prec NEG {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| NOT Exp {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 2, $1, $2);
}
| ID LP Args RP {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 4, $1, $2, $3, $4);
}
| ID LP RP {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp LB Exp RB {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 4, $1, $2, $3, $4);
}
| Exp DOT ID {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| ID {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| INT {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| FLOAT {
	$$ = createNode("Exp", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
}
| Exp ASSIGNOP error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp AND error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp OR error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp RELOP error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp PLUS error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp MINUS error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp STAR error {
	yyerror("Wrong expression");
	yyerrok;
}
| Exp DIV error {
	yyerror("Wrong expression");
	yyerrok;
}
| LP error RP {
	yyerror("Wrong expression");
	yyerrok;
}
| MINUS error {
	yyerror("Wrong expression");
	yyerrok;
}
| NOT error {
	yyerror("Wrong expression");
	yyerrok;
}
| ID LP error RP {
	yyerror("Wrong arguement(s)n");
	yyerrok;
}
| Exp LB error RB {
	yyerror("Missing \"]\"");
	yyerrok;
};

Args : Exp COMMA Args {
	$$ = createNode("Args", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 3, $1, $2, $3);
}
| Exp {
	$$ = createNode("Args", " ", @$.first_line, COMPLEX_);
	modifyTree($$, 1, $1);
};

%%

#include "lex.yy.c"

int yyerror(const char* msg, ...) {
	if (msg[0] != 's') {
		syntaxErrorCnt++;
		printf("Error type B at Line %d: %s.\n", yylineno, msg);
	}
}
