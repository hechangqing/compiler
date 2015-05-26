testbin = lexer-test parser-test
obj = lexer.o list-lexer.o list-parser.o

.PHONY: test all clean

all: $(obj) $(testbin)

test: all
	./lexer-test " [ a, b, c,ddd, e, f ]         "

parser-test: parser-test.cc list-parser.o list-lexer.o lexer.o
	g++ parser-test.cc list-parser.o list-lexer.o lexer.o -o parser-test
list-parser.o: list-parser.cc list-parser.h
	g++ -c list-parser.cc -o list-parser.o
lexer-test: lexer-test.cc list-lexer.o lexer.o
	g++ lexer-test.cc lexer.o list-lexer.o -o lexer-test
lexer.o: lexer.cc lexer.h
	g++ -c lexer.cc -o lexer.o
list-lexer.o: list-lexer.cc list-lexer.h lexer.cc lexer.h
	g++ -c list-lexer.cc -o list-lexer.o

clean:
	rm -f *.o $(testbin)
