TARGETS=itp
CFLAGS=-Wall -Werror -c

all: $(TARGETS)

itp: y.tab.c lex.yy.c
	gcc $^ -ll -o $@ 

lex.yy.c: source.lex
	flex source.lex 

y.tab.c: source.yacc
	yacc -v -d $^

run:
	./TARGETS