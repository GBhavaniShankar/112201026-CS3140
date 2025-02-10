PROGRAM = compiler
SOURCE = src
BIN = bin
INCLUDE = include

all:
	@echo "Building parser..."
	@yacc -d $(SOURCE)/$(PROGRAM).y -Wnone
	@lex $(SOURCE)/$(PROGRAM).l
	@mkdir -p $(BIN)
	@echo "Compiling source files..."
	@gcc -o $(BIN)/$(PROGRAM) lex.yy.c y.tab.c $(SOURCE)/$(PROGRAM).c -w -I ./$(INCLUDE)
	@echo "Build complete."

run: all
	@echo "Running program..."
	@./$(BIN)/$(PROGRAM)

clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN)/ y.tab.c lex.yy.c y.tab.h
	@echo "Cleanup complete."
