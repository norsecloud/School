p3: p3.tab.o lex.yy.o
	cc -o p3 lex.yy.o p3.tab.o

p3.tab.o: p3.tab.c
	cc -c p3.tab.c

p3.tab.c: p3.y
	bison -d p3.y

lex.yy.o: lex.yy.c p3.tab.h
	cc -c lex.yy.c

lex.yy.c: p3.l p3.tab.c
	flex p3.l
