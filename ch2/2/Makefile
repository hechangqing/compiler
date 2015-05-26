testbin = lexer-test
obj = lexer.o list-lexer.o

.PHONY: test all clean

all: $(obj) $(testbin)

test: all
	./lexer-test " [ a, b, c,ddd, e, f ]         "

lexer-test: lexer-test.cc list-lexer.o lexer.o
	g++ lexer-test.cc lexer.o list-lexer.o -o lexer-test
lexer.o: lexer.cc lexer.h
	g++ -c lexer.cc -o lexer.o
list-lexer.o: list-lexer.cc list-lexer.h lexer.cc lexer.h
	g++ -c list-lexer.cc -o list-lexer.o

clean:
	rm -f *.o $(testbin)
