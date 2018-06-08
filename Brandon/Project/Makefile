#
# Makefile for Project 1, Part 4
#

YACC       = bison -d -v
LEX        = flex
CC         = gcc
CPP        = g++ -g -Wno-deprecated --std=c++11
GAWK       = gawk
ASTBUILDER = astbuilder.gawk
TARGET     = csimple

OBJS += lexer.o parser.o main.o ast.o primitive.o ast2dot.o symtab.o typecheck.o
RMFILES = core.* *.dot *.pdf lexer.cpp parser.cpp parser.hpp parser.output ast.hpp ast.cpp error.log *.gch *.ps *.out $(TARGET) $(OBJS)
RMOBJ = core.* *.dot lexer.cpp parser.cpp parser.hpp parser.output ast.hpp ast.cpp *.gch *.ps $(TARGET) $(OBJS)

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

main.o: parser.hpp ast.hpp symtab.hpp primitive.hpp typecheck.cpp
ast2dot.o: parser.hpp ast.hpp symtab.hpp primitive.hpp attribute.hpp

ast.o: ast.cpp ast.hpp primitive.hpp symtab.hpp attribute.hpp
ast.cpp: ast.cdef
ast.hpp: ast.cdef

primitive.o: primitive.hpp primitive.cpp ast.hpp

removeDos: $(TESTFILES)
	dos2unix tests/validtest.1
	dos2unix tests/validtest.2
	dos2unix tests/validtest.3
	dos2unix tests/validtest.4
	dos2unix tests/invalidtest.1
	dos2unix tests/invalidtest.2
	dos2unix tests/invalidtest.3
	dos2unix tests/invalidtest.4

test: $(TARGET) $(TESTFILES)
	@echo "validtest.1" >> testoutput.out
	./$(TARGET) < tests/validtest.1 >> testoutput.out
	@echo "validtest.2" >> testoutput.out
	./$(TARGET) < tests/validtest.2 >> testoutput.out
	@echo "validtest.3" >> testoutput.out
	./$(TARGET) < tests/validtest.3 >> testoutput.out
	@echo "validtest.4" >> testoutput.out
	./$(TARGET) < tests/validtest.4 >> testoutput.out
	@echo "invalidtest.1" >> testoutput.out
	./$(TARGET) < tests/invalidtest.1 >> testoutput.out
	@echo "invalidtest.2" >> testoutput.out
	./$(TARGET) < tests/invalidtest.2 >> testoutput.out
	@echo "invalidtest.3" >> testoutput.out
	./$(TARGET) < tests/invalidtest.3 >> testoutput.out
	@echo "invalidtest.4" >> testoutput.out
	./$(TARGET) < tests/invalidtest.4 >> testoutput.out

test2pdf: $(TARGET) $(TESTFILES)
	@echo "validtest.1"
	./$(TARGET) < tests/validtest.1 >> test.good.output1.dot
	dot -Tps test.good.output1.dot > test.good.output1.ps
	ps2pdf test.good.output1.ps test.good.output1.pdf
	@echo "validtest.2"
	./$(TARGET) < tests/validtest.2 >> test.good.output2.dot
	dot -Tps test.good.output2.dot > test.good.output2.ps
	ps2pdf test.good.output2.ps test.good.output2.pdf
	@echo "validtest.3"
	./$(TARGET) < tests/validtest.3 >> test.good.output3.dot
	dot -Tps test.good.output3.dot > test.good.output3.ps
	ps2pdf test.good.output3.ps test.good.output3.pdf
	@echo "validtest.4"
	./$(TARGET) < tests/validtest.4 >> test.good.output4.dot
	dot -Tps test.good.output4.dot > test.good.output4.ps
	ps2pdf test.good.output4.ps test.good.output4.pdf
	@echo "invalidtest.1"
	./$(TARGET) < tests/invalidtest.1 >> test.bad.output1.dot
	dot -Tps test.bad.output1.dot > test.bad.output1.ps
	ps2pdf test.bad.output1.ps test.bad.output1.pdf
	@echo "invalidtest.2"
	./$(TARGET) < tests/invalidtest.2 >> test.bad.output2.dot
	dot -Tps test.bad.output2.dot > test.bad.output2.ps
	ps2pdf test.bad.output2.ps test.bad.output2.pdf
	@echo "invalidtest.3"
	./$(TARGET) < tests/invalidtest.3 >> test.bad.output3.dot
	dot -Tps test.bad.output2.dot > test.bad.output2.ps
	ps2pdf test.bad.output2.ps test.bad.output2.pdf
	@echo "invalidtest.4"
	./$(TARGET) < tests/invalidtest.4 >> test.bad.output4.dot
	dot -Tps test.bad.output2.dot > test.bad.output2.ps
	ps2pdf test.bad.output2.ps test.bad.output2.pdf

test1: $(TARGET)
	@echo "validtest.1" >> testoutput.out
	./$(TARGET) < tests/validtest.1 >> testoutput.out
	@echo "validtest.1"
	./$(TARGET) < tests/validtest.1 >> test.good.output1.dot
	dot -Tps test.good.output1.dot > test.good.output1.ps
	ps2pdf test.good.output1.ps test.good.output1.pdf

test2: $(TARGET)
	@echo "validtest.2" >> testoutput.out
	./$(TARGET) < tests/validtest.2 >> testoutput.out
	@echo "validtest.2"
	./$(TARGET) < tests/validtest.2 >> test.good.output2.dot
	dot -Tps test.good.output2.dot > test.good.output2.ps
	ps2pdf test.good.output2.ps test.good.output2.pdf

test3: $(TARGET)
	@echo "validtest.3" >> testoutput.out
	./$(TARGET) < tests/validtest.3 >> testoutput.out
	@echo "validtest.3"
	./$(TARGET) < tests/validtest.3 >> test.good.output3.dot
	dot -Tps test.good.output3.dot > test.good.output3.ps
	ps2pdf test.good.output3.ps test.good.output3.pdf

test4: $(TARGET)
	@echo "validtest.4" >> testoutput.out
	./$(TARGET) < tests/validtest.4 >> testoutput.out
	@echo "validtest.4"
	./$(TARGET) < tests/validtest.4 >> test.good.output4.dot
	dot -Tps test.good.output4.dot > test.good.output4.ps
	ps2pdf test.good.output4.ps test.good.output4.pdf

all: removeDos test test2pdf

clean:
	rm -f $(RMFILES)

cleanobj:
	rm -f $(RMOBJ)
