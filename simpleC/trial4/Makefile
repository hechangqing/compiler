GPPFLAG = -g -std=c++11
testbin = lexer-test parser-test ast-test symbol-test value-test\
          interpreter-test
objs = memory-space.o

.PHONY: test all

all: $(testbin) $(objs)

test: $(testbin)
	./lexer-test < test.c
	./parser-test < test3.c
	valgrind ./ast-test
	valgrind ./parser-test < test3.c
interpreter-test: interpreter-test.cc interpreter.o scope.o lexer.o parser.o symbol.o print-visitor.o
	g++ $(GPPFLAG) $< -o $@ interpreter.o scope.o lexer.o symbol.o parser.o print-visitor.o
value-test: value-test.cc value.h
	g++ $(GPPFLAG) $< -o $@
symbol-test: symbol-test.cc scope.o
	g++ $(GPPFLAG) $< scope.o -o $@
ast-test: ast-test.cc lexer.o ast.h
	g++ $(GPPFLAG) $< lexer.o -o $@
parser-test: parser-test.cc parser.o lexer.o print-visitor.o scope.o symbol.o
	g++ $(GPPFLAG) $< lexer.o parser.o print-visitor.o scope.o symbol.o -o $@
interpreter.o: interpreter.cc interpreter.h
	g++ $(GPPFLAG) -c $< -o $@
memory-space.o: memory-space.cc memory-space.h
	g++ $(GPPFLAG) -c $< -o $@
symbol.o: symbol.cc symbol.h
	g++ $(GPPFLAG) -c $< -o $@
scope.o: scope.cc scope.h symbol.h
	g++ $(GPPFLAG) -c $< -o $@
print-visitor.o: print-visitor.cc print-visitor.h ast.h
	g++ $(GPPFLAG) -c $< -o $@
parser.o: parser.cc parser.h
	g++ $(GPPFLAG) -c $< -o $@
lexer-test: lexer-test.cc lexer.o
	g++ $(GPPFLAG) $< lexer.o -o $@ 
lexer.o: lexer.cc lexer.h
	g++ $(GPPFLAG) -o $@ -c $<

clean:
	rm -f *.o $(testbin)

