CC = gcc

LEX_FILE = calc.l
YACC_FILE = calc.y
YACC_HEADER = y.tab.h
YACC_C = y.tab.c
LEX_C = lex.yy.c
EXECUTABLE = calc

all: $(EXECUTABLE)

$(EXECUTABLE): $(YACC_C) $(LEX_C)
	$(CC) $(YACC_C) $(LEX_C) -o $(EXECUTABLE) -ll

$(YACC_C) $(YACC_HEADER): $(YACC_FILE)
	yacc -d $(YACC_FILE)

$(LEX_C): $(LEX_FILE) $(YACC_HEADER)
	lex $(LEX_FILE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(YACC_C) $(YACC_HEADER) $(LEX_C)