%{
	#include "syntax.tab.h"
	int yycolumn = 1;
	int lexicalErrorCnt = 0;
	#define YY_USER_ACTION \
		yylloc.first_line = yylloc.last_line = yylineno; \
		yylloc.first_column = yycolumn; \
		yylloc.last_column = yycolumn + yyleng - 1; \
		yycolumn += yyleng;
%}

%option yylineno

digit [0-9]
letter [_a-zA-Z]
blanks [ \t\r]+
linebreak [\n]

INT 0|[1-9]{digit}*
FLOAT [0-9]*\.[0-9]+|[0-9]+\.
ID {letter}({letter}|{digit})*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS \+
MINUS -
STAR \*
DIV \/
AND "&&"
OR "||"
DOT "."
NOT !
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
MYSCHA .

%%

{blanks} {}
{linebreak} { yycolumn = 1; }

{INT} {
	yylval.type_node = createNode("INT", yytext, yylineno, INT_);
	return INT;
}
{FLOAT} {
	yylval.type_node = createNode("FLOAT", yytext, yylineno, FLOAT_);
	return FLOAT;
}
{STRUCT} {
	yylval.type_node = createNode("STRUCT", yytext, yylineno, STRUCT_);
	return STRUCT;
}
{RETURN} {
	yylval.type_node = createNode("RETURN", yytext, yylineno, RETURN_);
	return RETURN;
}
{IF} {
	yylval.type_node = createNode("IF", yytext, yylineno, IF_);
	return IF;
}
{ELSE} {
	yylval.type_node = createNode("ELSE", yytext, yylineno, ELSE_);
	return ELSE;
}
{WHILE} {
	yylval.type_node = createNode("WHILE", yytext, yylineno, WHILE_);
	return WHILE;
}
{TYPE} {
	yylval.type_node = createNode("TYPE", yytext, yylineno, TYPE_);
	return TYPE;
}
{SEMI} {
	yylval.type_node = createNode("SEMI", yytext, yylineno, SEMI_);
	return SEMI;
}
{COMMA} {
	yylval.type_node = createNode("COMMA", yytext, yylineno, COMMA_);
	return COMMA;
}
{ASSIGNOP} {
	yylval.type_node = createNode("ASSIGNOP", yytext, yylineno, ASSIGNOP_);
	return ASSIGNOP;
}
{RELOP} {
	yylval.type_node = createNode("RELOP", yytext, yylineno, RELOP_);
	return RELOP;
}
{PLUS} {
	yylval.type_node = createNode("PLUS", yytext, yylineno, PLUS_);
	return PLUS;
}
{MINUS} {
	yylval.type_node = createNode("MINUS", yytext, yylineno, MINUS_);
	return MINUS;
}
{STAR} {
	yylval.type_node = createNode("STAR", yytext, yylineno, STAR_);
	return STAR;
}
{DIV} {
	yylval.type_node = createNode("DIV", yytext, yylineno, DIV_);
	return DIV;
}
{AND} {
	yylval.type_node = createNode("AND", yytext, yylineno, AND_);
	return AND;
}
{OR} {
	yylval.type_node = createNode("OR", yytext, yylineno, OR_);
	return OR;
}
{DOT} {
	yylval.type_node = createNode("DOT", yytext, yylineno, DOT_);
	return DOT;
}
{NOT} {
	yylval.type_node = createNode("NOT", yytext, yylineno, NOT_);
	return NOT;
}
{LP} {
	yylval.type_node = createNode("LP", yytext, yylineno, LP_);
	return LP;
}
{RP} {
	yylval.type_node = createNode("RP", yytext, yylineno, RP_);
	return RP;
}
{LB} {
	yylval.type_node = createNode("LB", yytext, yylineno, LB_);
	return LB;
}
{RB} {
	yylval.type_node = createNode("RB", yytext, yylineno, RB_);
	return RB;
}
{LC} {
	yylval.type_node = createNode("LC", yytext, yylineno, LC_);
	return LC;
}
{RC} {
	yylval.type_node = createNode("RC", yytext, yylineno, RC_);
	return RC;
}
{ID} {
	yylval.type_node = createNode("ID", yytext, yylineno, ID_);
	return ID;
}
{MYSCHA} {
	lexicalErrorCnt++;
	printf("Error type A at Line %d: Mysterious character \'%s\'.\n", yylineno, yytext);
}

%%

/*int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex() != 0);
	return 0;
}*/
