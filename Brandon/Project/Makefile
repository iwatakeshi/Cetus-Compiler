#
# Makefile for Project 1, Part 1
#

define \n

endef

YACC    = bison -d -v
LEX     = flex
CC      = gcc
CPP     = g++ -g

TARGET  = csimple

TESTDIR = tests
OBJS += lexer.o parser.o main.o
RMFILES = core.* lexer.cpp parser.cpp parser.hpp parser.output testoutput.out $(TARGET) $(OBJS)
TESTFILES = $(wildcard $(TESTDIR)/*)

# Dependencies
$(TARGET): parser.cpp lexer.cpp parser.hpp $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

# Rules
%.cpp: %.ypp
	$(YACC) -o $(@:%.o=%.d) $<

%.o: %.cpp
	$(CPP) -o $@ -c $<

%.cpp: %.l
	$(LEX) -o$(@:%.o=%.d) $<

# Source
lexer.o: lexer.cpp parser.hpp
lexer.cpp: lexer.l

parser.o: parser.cpp parser.hpp
parser.cpp: parser.ypp

main.o: parser.hpp

removeDos: $(TESTFILES)
	dos2unix tests/validtest.1
	dos2unix tests/validtest.2
	dos2unix tests/validtest.3
	dos2unix tests/validtest.4
	dos2unix tests/test.1
	dos2unix tests/test.2
	dos2unix tests/test.3
	dos2unix tests/test.4
	dos2unix tests/test.5
	dos2unix tests/invalidtest.1

test: $(TARGET) $(TESTFILES)
	@echo "validtest.1" >> testoutput.out
	./$(TARGET) < tests/validtest.1 >> testoutput.out
	@echo "validtest.2" >> testoutput.out
	./$(TARGET) < tests/validtest.2 >> testoutput.out
	@echo "validtest.3" >> testoutput.out
	./$(TARGET) < tests/validtest.3 >> testoutput.out
	@echo "validtest.4" >> testoutput.out
	./$(TARGET) < tests/validtest.4 >> testoutput.out
	@echo "test.1" >> testoutput.out
	./$(TARGET) < tests/test.1 >> testoutput.out
	@echo "test.2" >> testoutput.out
	./$(TARGET) < tests/test.2 >> testoutput.out
	@echo "test.3" >> testoutput.out
	./$(TARGET) < tests/test.3 >> testoutput.out
	@echo "test.4" >> testoutput.out
	./$(TARGET) < tests/test.4 >> testoutput.out
	@echo "test.5" >> testoutput.out
	./$(TARGET) < tests/test.5 >> testoutput.out
	@echo "invalidtest.1" >> testoutput.out
	./$(TARGET) < tests/invalidtest.1 >> testoutput.out

all: removeDos test

clean:
	rm -f $(RMFILES)
