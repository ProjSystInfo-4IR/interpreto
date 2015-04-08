TARGETS=itp
CFLAGS=-Wall -Werror -c

all: $(TARGETS)

itp: y.tab.c lex.yy.c code.o mem.o
	gcc $^ -ll -o $@ 

code.o: code.c code.h
	gcc $(CFLAGS) code.c -o $@

interpret.o: interpret.c interpret.h
	gcc $(CFLAGS) interpret.c -o $@

mem.o: mem.c mem.h 
	gcc $(CFLAGS) mem.c -o $@

lex.yy.c: source.lex
	flex source.lex 

y.tab.c: source.yacc
	yacc -v -d $^

run:
	./TARGETS