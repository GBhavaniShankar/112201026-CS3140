PROGRAM = compiler
SOURCE = src
BIN = bin
INCLUDE = include
SRCS    = src/sym_tab.c src/statement.c src/asm.c

all:
	@yacc -d $(SOURCE)/$(PROGRAM).y
	@lex $(SOURCE)/$(PROGRAM).l
	@mkdir -p $(BIN)
	@gcc -o $(BIN)/$(PROGRAM) lex.yy.c y.tab.c $(SRCS) -w -I ./$(INCLUDE)

clean:
	@rm -rf $(BIN)/ y.tab.c lex.yy.c y.tab.h
