TARGETS=itp
CFLAGS=-Wall -Werror -c

all: $(TARGETS)

itp: y.tab.c lex.yy.c code.o mem.o logger.o
	gcc $^ -ll -o $@ 

clean:
	rm *.o
	
code.o: code.c code.h
	gcc $(CFLAGS) code.c -o $@

logger.o: dumb-logger/logger.c dumb-logger/logger.h
	gcc $(CFLAGS) dumb-logger/logger.c -o $@

mem.o: mem.c mem.h 
	gcc $(CFLAGS) mem.c -o $@

lex.yy.c: source.lex
	flex source.lex 

y.tab.c: source.yacc
	yacc -v -d $^

run:
	./TARGETS