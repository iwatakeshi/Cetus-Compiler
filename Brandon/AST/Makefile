#
# Makefile for Project 1, Part 2
#

YACC       = bison -d -v
LEX        = flex
CC         = gcc
CPP        = g++ -g -Wno-deprecated --std=c++11
GAWK       = gawk
ASTBUILDER = astbuilder.gawk
TARGET     = csimple

OBJS += lexer.o parser.o main.o ast.o primitive.o  ast2dot.o symtab.o
RMFILES = core.* lexer.cpp parser.cpp parser.hpp parser.output ast.hpp ast.cpp *.ps *.pdf *.dot *.out $(TARGET) $(OBJS)

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

ast.o: ast.cpp ast.hpp primitive.hpp symtab.hpp attribute.hpp
ast.cpp: ast.cdef
ast.hpp: ast.cdef

primitive.o: primitive.hpp primitive.cpp ast.hpp

removeDos: $(TESTFILES)
	dos2unix tests/validtest.1
	dos2unix tests/validtest.2
	dos2unix tests/validtest.3
	dos2unix tests/validtest.4
	dos2unix tests/validtest.5
	dos2unix tests/validtest.6
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
	@echo "validtest.5" >> testoutput.out
	./$(TARGET) < tests/validtest.5 >> testoutput.out
	@echo "validtest.6" >> testoutput.out
	./$(TARGET) < tests/validtest.6 >> testoutput.out
	@echo "invalidtest.1" >> testoutput.out
	./$(TARGET) < tests/invalidtest.1 >> testoutput.out
	@echo "invalidtest.2" >> testoutput.out
	./$(TARGET) < tests/invalidtest.2 >> testoutput.out
	@echo "invalidtest.3" >> testoutput.out
	./$(TARGET) < tests/invalidtest.3 >> testoutput.out
	@echo "invalidtest.4" >> testoutput.out
	./$(TARGET) < tests/invalidtest.4 >> testoutput.out

test2pdf: $(TARGET) $(TESTFILES)
	@echo "test1.lang"
	./$(TARGET) < tests/test1.lang >> test1.lang.dot
	dot -Tps test1.lang.dot > test1.lang.ps
	ps2pdf test1.lang.ps test1.lang.pdf
	@echo "test2.lang"
	./$(TARGET) < tests/test2.lang >> test2.lang.dot
	dot -Tps test2.lang.dot > test2.lang.ps
	ps2pdf test2.lang.ps test2.lang.pdf
	@echo "test3.lang"
	./$(TARGET) < tests/test3.lang >> test3.lang.dot
	dot -Tps test3.lang.dot > test3.lang.ps
	ps2pdf test3.lang.ps test3.lang.pdf
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
	@echo "validtest.5"
	./$(TARGET) < tests/validtest.5 >> test.good.output5.dot
	dot -Tps test.good.output5.dot > test.good.output5.ps
	ps2pdf test.good.output5.ps test.good.output5.pdf
	@echo "validtest.6"
	./$(TARGET) < tests/validtest.6 >> test.good.output6.dot
	dot -Tps test.good.output6.dot > test.good.output6.ps
	ps2pdf test.good.output6.ps test.good.output6.pdf
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


all: removeDos test

clean:
	rm -f $(RMFILES)
