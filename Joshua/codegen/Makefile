#
# Makefile for Project 1, Part 5
#

YACC       = bison -d -v
LEX        = flex
CC         = gcc
CPP        = g++ -g -Wno-deprecated --std=c++11
GAWK       = gawk
ASTBUILDER = astbuilder.gawk
TARGET     = csimple

OBJS += lexer.o parser.o main.o ast.o primitive.o ast2dot.o symtab.o typecheck.o codegen.o
RMFILES = core.* *.dot *.pdf lexer.cpp parser.cpp parser.hpp parser.output ast.hpp ast.cpp *.s $(TARGET) $(OBJS)

# dependencies
$(TARGET): parser.cpp lexer.cpp parser.hpp $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

# rules
%.cpp: %.ypp
	$(YACC) -o $(@:%.o=%.d) $<

%.o: %.cpp
	$(CPP) -o $@ -c $<

%.cpp: %.l
	$(LEX) -o$(@:%.o=%.d)  $<

ast.cpp: ast.cdef
	$(GAWK) -f $(ASTBUILDER) -v outtype=cpp -v outfile=ast.cpp < ast.cdef

ast.hpp: ast.cdef
	$(GAWK) -f $(ASTBUILDER) -v outtype=hpp -v outfile=ast.hpp < ast.cdef

# source
lexer.o: lexer.cpp parser.hpp ast.hpp
lexer.cpp: lexer.l

parser.o: parser.cpp parser.hpp
parser.cpp: parser.ypp ast.hpp primitive.hpp symtab.hpp

main.o: parser.hpp ast.hpp symtab.hpp primitive.hpp
ast2dot.o: parser.hpp ast.hpp symtab.hpp primitive.hpp attribute.hpp
typecheck.o: parser.hpp ast.hpp symtab.hpp primitive.hpp attribute.hpp

ast.o: ast.cpp ast.hpp primitive.hpp symtab.hpp attribute.hpp
ast.cpp: ast.cdef
ast.hpp: ast.cdef

primitive.o: primitive.hpp primitive.cpp ast.hpp
symtab.o: symtab.hpp symtab.cpp ast.hpp attribute.hpp

test: $(TARGET) $(TESTFILES)
	@echo "validtest.1"
	./$(TARGET) < tests/validtest.1 >> validtest1.s
	gcc -c -m32 -o csimple.o validtest1.s
	gcc -c -m32 -o start.o start.c
	gcc -m32 -o start1 start.o csimple.o
	@echo "validtest.2"
	./$(TARGET) < tests/validtest.2 >> validtest2.s
	gcc -c -m32 -o csimple.o validtest2.s
	gcc -c -m32 -o start.o start.c
	gcc -m32 -o start2 start.o csimple.o
	@echo "validtest.3"
	./$(TARGET) < tests/validtest.3 >> validtest3.s
	gcc -c -m32 -o csimple.o validtest3.s
	gcc -c -m32 -o start.o start.c
	gcc -m32 -o start3 start.o csimple.o
	@echo "validtest.2"
	./$(TARGET) < tests/validtest.4 >> validtest4.s
	gcc -c -m32 -o csimple.o validtest4.s
	gcc -c -m32 -o start.o start.c
	gcc -m32 -o start4 start.o csimple.o

clean:
	rm -f $(RMFILES)
