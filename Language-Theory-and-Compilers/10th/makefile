test : complex.exe test.in test.check
	./complex.exe <test.in >test.out
	diff test.out test.check

complex.exe : complex.tab.o lex.yy.o
	gcc -o complex.exe complex.tab.o lex.yy.o -lm

complex.tab.o : complex.tab.c
	gcc -c complex.tab.c

complex.tab.c : complex.y
	bison -d -v complex.y

lex.yy.o : lex.yy.c complex.tab.h
	gcc -c lex.yy.c

lex.yy.c : complex.l
	flex -I complex.l

complex.tab.h : complex.y
	bison -d -v complex.y