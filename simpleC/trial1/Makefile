GPPFLAG = -g
testbin = lexer-test

.PHONY: test all

all: $(testbin)

test: $(testbin)
	./lexer-test < test.c
lexer-test: lexer-test.cc lexer.o
	g++ $(GPPFLAG) $< lexer.o -o $@ 
lexer.o: lexer.cc lexer.h
	g++ $(GPPFLAG) -o $@ -c $<

clean:
	rm *.o $(testbin)

