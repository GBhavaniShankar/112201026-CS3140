#include "compiler.h"

Symbol *symbol_table[TABLE_SIZE];

void init_symbol_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbol_table[i] = NULL;
    }
}

unsigned int hash(const char *key)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

Symbol *create_symbol(const char *key)
{
    Symbol *symbol = search_symbol(key);
    if (symbol == NULL)
    {
        unsigned int index = hash(key);
        Symbol *new_symbol = malloc(sizeof(Symbol));
        if (!new_symbol)
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        new_symbol->name = strdup(key);
        if (!new_symbol->name)
        {
            fprintf(stderr, "Memory allocation error for name\n");
            exit(EXIT_FAILURE);
        }
        new_symbol->next = symbol_table[index];
        symbol_table[index] = new_symbol;
        return new_symbol;
    }
    else
    {
        fprintf(stderr, "The symbol %s already exists..!", key);
        exit(EXIT_FAILURE);
    }
}

void create_symbol_int(const char *key)
{
    Symbol *symbol = create_symbol(key);
    symbol->type = SYMBOL_INT;
    symbol->value.int_value.value = 0;
    symbol->value.int_value.is_defined = false;
}

void create_symbol_int_array(const char *key, int size)
{
    Symbol *symbol = create_symbol(key);
    symbol->type = SYMBOL_INT_ARRAY;
    symbol->value.int_array.size = size;
    symbol->value.int_array.array = malloc(sizeof(int) * size);
    if (!symbol->value.int_array.array)
    {
        fprintf(stderr, "Memory allocation error for int array\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
        symbol->value.int_array.array[i] = 0;
}

void create_symbol_bool(const char *key)
{
    Symbol *symbol = create_symbol(key);
    symbol->type = SYMBOL_BOOL;
    symbol->value.bool_value.value = false;
    symbol->value.bool_value.is_defined = false;
}

void create_symbol_bool_array(const char *key, int size)
{
    Symbol *symbol = create_symbol(key);
    symbol->type = SYMBOL_BOOL_ARRAY;
    symbol->value.bool_array.size = size;
    symbol->value.bool_array.array = malloc(sizeof(bool) * size);
    if (!symbol->value.bool_array.array)
    {
        fprintf(stderr, "Memory allocation error for bool array\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
        symbol->value.bool_array.array[i] = false;
}

Symbol *search_symbol(const char *key)
{
    unsigned int index = hash(key);
    Symbol *current = symbol_table[index];
    while (current != NULL)
    {
        if (strcmp(current->name, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void update_symbol_int(const char *key, int value)
{
    Symbol *symbol = search_symbol(key);
    if (symbol && symbol->type == SYMBOL_INT)
    {
        symbol->value.int_value.value = value;
        symbol->value.int_value.is_defined = true;
    }
    else
    {
        fprintf(stderr, "Symbol not found or type mismatch for %s\n", key);
    }
}

void update_symbol_int_array(const char *key, int index, int value)
{
    Symbol *symbol = search_symbol(key);
    if (symbol && symbol->type == SYMBOL_INT_ARRAY)
    {
        if (index >= 0 && index < symbol->value.int_array.size)
        {
            symbol->value.int_array.array[index] = value;
        }
        else
        {
            fprintf(stderr, "Index out of bounds for int array %s\n", key);
        }
    }
    else
    {
        fprintf(stderr, "Symbol not found or type mismatch for %s\n", key);
    }
}

void update_symbol_bool(const char *key, int value)
{
    Symbol *symbol = search_symbol(key);
    if (symbol && symbol->type == SYMBOL_BOOL)
    {
        symbol->value.bool_value.value = value;
        symbol->value.bool_value.is_defined = true;
    }
    else
    {
        fprintf(stderr, "Symbol not found or type mismatch for %s\n", key);
    }
}

void update_symbol_bool_array(const char *key, int index, int value)
{
    Symbol *symbol = search_symbol(key);
    if (symbol && symbol->type == SYMBOL_BOOL_ARRAY)
    {
        if (index >= 0 && index < symbol->value.bool_array.size)
        {
            symbol->value.bool_array.array[index] = value;
        }
        else
        {
            fprintf(stderr, "Index out of bounds for bool array %s\n", key);
        }
    }
    else
    {
        fprintf(stderr, "Symbol not found or type mismatch for %s\n", key);
    }
}

int lookup_int(const char *key)
{
    Symbol *symbol = search_symbol(key);
    if (!symbol)
    {
        fprintf(stderr, "Symbol not found: %s\n", key);
        exit(EXIT_FAILURE);
    }
    if (symbol->type != SYMBOL_INT)
    {
        fprintf(stderr, "Symbol type mismatch for %s: expected int\n", key);
        exit(EXIT_FAILURE);
    }
    if (!symbol->value.int_value.is_defined)
    {
        fprintf(stderr, "Symbol %s is not defined.\n", key);
        exit(EXIT_FAILURE);
    }
    return symbol->value.int_value.value;
}

int lookup_int_arr(const char *key, int index)
{
    Symbol *symbol = search_symbol(key);
    if (!symbol)
    {
        fprintf(stderr, "Symbol not found: %s\n", key);
        exit(EXIT_FAILURE);
    }
    if (symbol->type != SYMBOL_INT_ARRAY)
    {
        fprintf(stderr, "Symbol type mismatch for %s: expected int array\n", key);
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= symbol->value.bool_array.size)
    {
        fprintf(stderr, "Index out of bounds for int array %s\n", key);
        exit(EXIT_FAILURE);
    }
    return symbol->value.int_array.array[index];
}

bool lookup_bool(const char *key)
{
    Symbol *symbol = search_symbol(key);
    if (!symbol)
    {
        fprintf(stderr, "Symbol not found: %s\n", key);
        exit(EXIT_FAILURE);
    }
    if (symbol->type != SYMBOL_BOOL)
    {
        fprintf(stderr, "Symbol type mismatch for %s: expected bool\n", key);
        exit(EXIT_FAILURE);
    }
    if (!symbol->value.bool_value.is_defined)
    {
        fprintf(stderr, "Symbol %s is not defined.\n", key);
        exit(EXIT_FAILURE);
    }
    return symbol->value.bool_value.value;
}

bool lookup_bool_arr(const char *key, int index)
{
    Symbol *symbol = search_symbol(key);
    if (!symbol)
    {
        fprintf(stderr, "Symbol not found: %s\n", key);
        exit(EXIT_FAILURE);
    }
    if (symbol->type != SYMBOL_BOOL_ARRAY)
    {
        fprintf(stderr, "Symbol type mismatch for %s: expected bool array\n", key);
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= symbol->value.bool_array.size)
    {
        fprintf(stderr, "Index out of bounds for bool array %s\n", key);
        exit(EXIT_FAILURE);
    }
    return symbol->value.bool_array.array[index];
}

void free_symbol(Symbol *symbol)
{
    if (!symbol)
        return;
    free(symbol->name);
    switch (symbol->type)
    {
    case SYMBOL_INT:
        /* no extra allocation */
        break;
    case SYMBOL_INT_ARRAY:
        free(symbol->value.int_array.array);
        break;
    case SYMBOL_BOOL:
        /* no extra allocation */
        break;
    case SYMBOL_BOOL_ARRAY:
        free(symbol->value.bool_array.array);
        break;
    }
    free(symbol);
}

void free_symbol_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Symbol *current = symbol_table[i];
        while (current)
        {
            Symbol *temp = current;
            current = current->next;
            free_symbol(temp);
        }
        symbol_table[i] = NULL;
    }
}

void print_symbol_table()
{
    // Helper structure to store a row's data.
    typedef struct
    {
        char *name;
        char *type;
        char **value_lines; // For multi-line cells (e.g., 2D arrays)
        int num_value_lines;
    } TableRow;

    // First, count the total number of symbols.
    int num_symbols = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (Symbol *cur = symbol_table[i]; cur != NULL; cur = cur->next)
            num_symbols++;
    }

    // Allocate an array to hold each row's data.
    TableRow *rows = malloc(sizeof(TableRow) * num_symbols);
    int row_index = 0;
    char buffer[1024]; // Working buffer

    // Traverse the symbol table and build string representations.
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (Symbol *cur = symbol_table[i]; cur != NULL; cur = cur->next)
        {
            // Copy the symbol name.
            rows[row_index].name = strdup(cur->name);

            // Set the type string.
            char type_buf[50];
            switch (cur->type)
            {
            case SYMBOL_INT:
                strcpy(type_buf, "INT");
                break;
            case SYMBOL_INT_ARRAY:
                strcpy(type_buf, "INT ARRAY");
                break;
            case SYMBOL_BOOL:
                strcpy(type_buf, "BOOL");
                break;
            case SYMBOL_BOOL_ARRAY:
                strcpy(type_buf, "BOOL ARRAY");
                break;
            default:
                strcpy(type_buf, "N/A");
                break;
            }
            rows[row_index].type = strdup(type_buf);

            // Build the value cell(s)
            rows[row_index].value_lines = NULL;
            rows[row_index].num_value_lines = 0;
            if (cur->type == SYMBOL_INT)
            {
                rows[row_index].num_value_lines = 1;
                rows[row_index].value_lines = malloc(sizeof(char *));
                if (cur->value.int_value.is_defined)
                    snprintf(buffer, sizeof(buffer), "%d", cur->value.int_value.value);
                else
                    snprintf(buffer, sizeof(buffer), "UNDEF");
                rows[row_index].value_lines[0] = strdup(buffer);
            }
            else if (cur->type == SYMBOL_INT_ARRAY)
            {
                rows[row_index].num_value_lines = 1;
                rows[row_index].value_lines = malloc(sizeof(char *));
                buffer[0] = '\0';
                strcpy(buffer, "[");
                for (int j = 0; j < cur->value.int_array.size; j++)
                {
                    char num_buf[64];
                    snprintf(num_buf, sizeof(num_buf), "%d", cur->value.int_array.array[j]);
                    strcat(buffer, num_buf);
                    if (j < cur->value.int_array.size - 1)
                        strcat(buffer, ", ");
                }
                strcat(buffer, "]");
                rows[row_index].value_lines[0] = strdup(buffer);
            }
            else if (cur->type == SYMBOL_BOOL)
            {
                rows[row_index].num_value_lines = 1;
                rows[row_index].value_lines = malloc(sizeof(char *));
                if (cur->value.bool_value.is_defined)
                    snprintf(buffer, sizeof(buffer), "%s", cur->value.bool_value.value ? "true" : "false");
                else
                    snprintf(buffer, sizeof(buffer), "UNDEF");
                rows[row_index].value_lines[0] = strdup(buffer);
            }
            else if (cur->type == SYMBOL_BOOL_ARRAY)
            {
                rows[row_index].num_value_lines = 1;
                rows[row_index].value_lines = malloc(sizeof(char *));
                buffer[0] = '\0';
                strcpy(buffer, "[");
                for (int j = 0; j < cur->value.bool_array.size; j++)
                {
                    char num_buf[64];
                    snprintf(num_buf, sizeof(num_buf), "%s", cur->value.bool_array.array[j] ? "true" : "false");
                    strcat(buffer, num_buf);
                    if (j < cur->value.bool_array.size - 1)
                        strcat(buffer, ", ");
                }
                strcat(buffer, "]");
                rows[row_index].value_lines[0] = strdup(buffer);
            }
            row_index++;
        }
    }

    // Determine the maximum width for each column.
    int max_name_width = (int)strlen("Name");
    int max_type_width = (int)strlen("Type");
    int max_value_width = (int)strlen("Value");
    for (int i = 0; i < num_symbols; i++)
    {
        int len = (int)strlen(rows[i].name);
        if (len > max_name_width)
            max_name_width = len;
        len = (int)strlen(rows[i].type);
        if (len > max_type_width)
            max_type_width = len;
        for (int j = 0; j < rows[i].num_value_lines; j++)
        {
            int vlen = (int)strlen(rows[i].value_lines[j]);
            if (vlen > max_value_width)
                max_value_width = vlen;
        }
    }

    // Calculate the total width of the table.
    // The format: "║ " + name + " │ " + type + " │ " + value + " ║"
    int total_width = max_name_width + max_type_width + max_value_width + 10;

    // Print the top border (double-line) in cyan.
    printf(CYAN "╔");
    for (int i = 0; i < total_width - 2; i++)
        printf("═");
    printf("╗\n" RESET);

    // Print the centered header "SYMBOL TABLE" inside the borders.
    char header[] = "SYMBOL TABLE";
    int header_len = (int)strlen(header);
    int left_padding = (total_width - header_len) / 2 - 2;
    int right_padding = total_width - header_len - left_padding - 2;
    printf(CYAN "║%*s" RESET CYAN BOLD "%s" RESET CYAN "%*s║\n", left_padding, "", header, right_padding, "");

    // Print header separator row after the header.
    printf(CYAN "╠");
    for (int i = 0; i < total_width - 2; i++)
        printf("─");
    printf("╣\n" RESET);

    // Print column headers.
    printf(CYAN "║ " BLUE BOLD "%-*s" RESET CYAN " │ " BLUE BOLD "%-*s" CYAN RESET CYAN " │ " BLUE BOLD "%-*s" RESET CYAN " ║\n" RESET,
           max_name_width, "Name", max_type_width, "Type", max_value_width, "Value");

    // Print header-data separator.
    printf(CYAN "╠");
    for (int i = 0; i < max_name_width + 2; i++)
        printf("─");
    printf("┼");
    for (int i = 0; i < max_type_width + 2; i++)
        printf("─");
    printf("┼");
    for (int i = 0; i < max_value_width + 2; i++)
        printf("─");
    printf("╣\n" RESET);

    // Print each row of data.
    int printed_rows = 0;
    for (int i = 0; i < num_symbols; i++)
    {
        int lines = rows[i].num_value_lines;
        for (int line = 0; line < lines; line++)
        {
            if (line == 0)
            {
                // Print the first line with symbol name and type.
                printf(CYAN "║ " RESET GREEN "%-*s" RESET CYAN " │ " RESET MAGENTA "%-*s" RESET CYAN " │ " RESET YELLOW "%-*s" RESET CYAN " ║\n" RESET,
                       max_name_width, rows[i].name,
                       max_type_width, rows[i].type,
                       max_value_width, rows[i].value_lines[line]);
            }
            else
            {
                // Subsequent lines for multi-line cells.
                printf("║ %-*s │ %-*s │ " YELLOW "%-*s" RESET " ║\n",
                       max_name_width, "",
                       max_type_width, "",
                       max_value_width, rows[i].value_lines[line]);
            }
        }
        printed_rows++;
        if (printed_rows < num_symbols)
        {
            printf(CYAN "╟");
            for (int j = 0; j < max_name_width + 2; j++)
                printf("─");
            printf("┼");
            for (int j = 0; j < max_type_width + 2; j++)
                printf("─");
            printf("┼");
            for (int j = 0; j < max_value_width + 2; j++)
                printf("─");
            printf("╢\n" RESET);
        }
    }

    // Print the bottom border (double-line) in cyan.
    printf(CYAN "╚");
    for (int i = 0; i < total_width - 2; i++)
        printf("═");
    printf("╝\n" RESET);

    // Free allocated memory.
    for (int i = 0; i < num_symbols; i++)
    {
        free(rows[i].name);
        free(rows[i].type);
        for (int j = 0; j < rows[i].num_value_lines; j++)
        {
            free(rows[i].value_lines[j]);
        }
        free(rows[i].value_lines);
    }
    free(rows);
}