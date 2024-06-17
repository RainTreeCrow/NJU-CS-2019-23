all:parser
parser:
	flex -o ./lex.yy.c ./lexical.l
	bison -o ./syntax.tab.c -d -v ./syntax.y
	gcc -c ./syntax.tab.c -o ./syntax.tab.o
	gcc -std=c99   -c -o semantic.o semantic.c
	gcc -std=c99   -c -o intermediate.o intermediate.c
	gcc -std=c99   -c -o main.o main.c
	gcc -std=c99   -c -o assembly.o assembly.c
	gcc -std=c99   -c -o lib.o lib.c
	gcc -o parser ./semantic.o ./intermediate.o ./main.o ./assembly.o ./lib.o ./syntax.tab.o -lfl -ly
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f ./semantic.o ./intermediate.o ./main.o ./assembly.o ./lib.o ./syntax.tab.o ./lex.yy.o ./semantic.d ./intermediate.d ./main.d ./assembly.d ./lib.d ./syntax.tab.d ./lex.yy.d
	rm -f ./lex.yy.c ./syntax.tab.c ./syntax.tab.h
	rm -f *~
