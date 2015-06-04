GPPFLAG = -g
testbin = lexer-test parser-test

.PHONY: test all

all: $(testbin)

test: $(testbin)
	./lexer-test < test.c
	./parser-test < test3.c
parser-test: parser-test.cc parser.o lexer.o
	g++ $(GPPFLAG) $< lexer.o parser.o -o $@
parser.o: parser.cc parser.h
	g++ $(GPPFLAG) -c $< -o $@
lexer-test: lexer-test.cc lexer.o
	g++ $(GPPFLAG) $< lexer.o -o $@ 
lexer.o: lexer.cc lexer.h
	g++ $(GPPFLAG) -o $@ -c $<

clean:
	rm -f *.o $(testbin)

