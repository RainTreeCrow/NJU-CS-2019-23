#include <stdio.h>
#include "semantic.h"
#include "intermediate.h"

int yyrestart();
int yyparse();
extern int lexicalErrorCnt;
extern int syntaxErrorCnt;
//extern struct Node* treeRoot;
//void printTree(struct Node* root, int depth);

int main(int argc, char** argv)
{
	if (argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if (!f)
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	yyparse();
    if (lexicalErrorCnt == 0 && syntaxErrorCnt == 0) {
        //printTree(treeRoot, 0);
		int ok = semanticCheck(treeRoot);
		if (ok == 1) {
			if (argc >= 3) {
				char filename[32];
				strcpy(filename, argv[2]);
				intermediateCode(treeRoot, filename);
			}
		}
	}
	return 0;
}
