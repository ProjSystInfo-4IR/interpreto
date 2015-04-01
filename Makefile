TARGETS=itp
CFLAGS=-Wall -Werror -c

all: $(TARGETS)

itp: y.tab.c lex.yy.c mem.o
	gcc $^ -ll -o $@ 

mem.o: mem.c mem.h 
	gcc $(CFLAGS) mem.c -o $@

lex.yy.c: source.lex
	flex source.lex 

y.tab.c: source.yacc
	yacc -v -d $^

run:
	./TARGETS