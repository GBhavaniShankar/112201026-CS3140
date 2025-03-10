#include "compiler.h"

bool breakFlag = false;

unsigned int hash(const char *key)
{
    unsigned int hash_value = 0;
    while (*key)
    {
        hash_value = (hash_value * 31) + *key;
        key++;
    }
    return hash_value % TABLE_SIZE;
}

Symbol *symbol_table[TABLE_SIZE] = {NULL};

void init_symbol_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbol_table[i] = NULL;
    }
}

Symbol *create_symbol(const char *name, SymbolType type)
{
    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->next = NULL;
    return new_symbol;
}

void create_symbol_int(const char *key)
{
    unsigned int index = hash(key);
    Symbol *new_symbol = create_symbol(key, SYMBOL_INT);
    new_symbol->value.int_value.value = 0;
    new_symbol->value.int_value.is_defined = false;
    new_symbol->next = symbol_table[index];
    symbol_table[index] = new_symbol;
}

void create_symbol_float(const char *key)
{
    unsigned int index = hash(key);
    Symbol *new_symbol = create_symbol(key, SYMBOL_FLOAT);
    new_symbol->value.float_value.value = 0;
    new_symbol->value.float_value.is_defined = false;
    new_symbol->next = symbol_table[index];
    symbol_table[index] = new_symbol;
}

void update_symbol_int(const char *key, int new_value)
{
    Symbol *sym = search_symbol(key);
    if (sym && sym->type == SYMBOL_INT)
    {
        sym->value.int_value.value = new_value;
        sym->value.int_value.is_defined = true;
    }
    else
    {
        printf("Error: Symbol %s not found or type mismatch\n", key);
    }
}

void create_symbol_array(const char *key, int size)
{
    unsigned int index = hash(key);
    Symbol *new_symbol = create_symbol(key, SYMBOL_INT_ARRAY);
    new_symbol->value.int_array.array = (int *)calloc(size, sizeof(int));
    new_symbol->value.int_array.size = size;
    new_symbol->next = symbol_table[index];
    symbol_table[index] = new_symbol;
}

void create_symbol_2d_array(const char *key, int size1, int size2)
{
    unsigned int index = hash(key);
    Symbol *new_symbol = create_symbol(key, SYMBOL_INT_2D_ARRAY);
    new_symbol->value.int_2d_arr.arr = (int **)calloc(size1, sizeof(int *));
    for (int i = 0; i < size1; i++)
    {
        new_symbol->value.int_2d_arr.arr[i] = (int *)calloc(size2, sizeof(int));
    }
    new_symbol->value.int_2d_arr.size1 = size1;
    new_symbol->value.int_2d_arr.size2 = size2;
    new_symbol->next = symbol_table[index];
    symbol_table[index] = new_symbol;
}

void update_symbol_array(const char *key, int index, int value)
{
    Symbol *sym = search_symbol(key);
    if (sym && sym->type == SYMBOL_INT_ARRAY)
    {
        if (index >= 0 && index < sym->value.int_array.size)
        {
            sym->value.int_array.array[index] = value;
        }
        else
        {
            printf("Error: Index out of bounds for array %s\n", key);
        }
    }
    else
    {
        printf("Error: Symbol %s not found or type mismatch\n", key);
    }
}

Symbol *search_symbol(const char *key)
{
    unsigned int index = hash(key);
    Symbol *sym = symbol_table[index];
    while (sym)
    {
        if (strcmp(sym->name, key) == 0)
        {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}

void free_symbol(Symbol *sym)
{
    if (!sym)
        return;
    free(sym->name);
    if (sym->type == SYMBOL_INT_ARRAY)
    {
        free(sym->value.int_array.array);
    }
    free(sym);
}

void free_symbol_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Symbol *sym = symbol_table[i];
        while (sym)
        {
            Symbol *temp = sym;
            sym = sym->next;
            free_symbol(temp);
        }
    }
}

void print_symbol_table()
{
    const int nameWidth = 20;
    const int typeWidth = 15;
    const int valueWidth = 50;
    const int totalWidth = nameWidth + typeWidth + valueWidth + 4; // extra for separators

    // Top border (left border only)
    printf("╔");
    for (int i = 0; i < totalWidth - 1; i++)
        printf("═");
    printf("\n");

    // Print title centered with left border only
    char title[] = "SYMBOL TABLE";
    int titleLen = strlen(title);
    int padding = (totalWidth - 1 - titleLen) / 2;
    printf("║");
    for (int i = 0; i < padding; i++)
        printf(" ");
    printf("%s\n", title);

    // Print header row without a trailing right border
    printf("║ %-*s │ %-*s │ %-*s\n",
           nameWidth, "Name",
           typeWidth, "Type",
           valueWidth, "Value");

    // Print divider line
    printf("╟");
    for (int i = 0; i < nameWidth; i++)
        printf("─");
    printf("┼");
    for (int i = 0; i < typeWidth; i++)
        printf("─");
    printf("┼");
    for (int i = 0; i < valueWidth; i++)
        printf("─");
    printf("\n");

    // Iterate through the symbol table and print each symbol
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (Symbol *sym = symbol_table[i]; sym != NULL; sym = sym->next)
        {
            char typeStr[32] = "";
            char valueStr[2048] = "";
            switch (sym->type)
            {
            case SYMBOL_INT:
                strcpy(typeStr, "INT");
                if (sym->value.int_value.is_defined)
                    sprintf(valueStr, "%d", sym->value.int_value.value);
                else
                    strcpy(valueStr, "UNDEF");
                break;
            case SYMBOL_FLOAT:
                strcpy(typeStr, "FLOAT");
                if (sym->value.float_value.is_defined)
                    sprintf(valueStr, "%.2f", sym->value.float_value.value);
                else
                    strcpy(valueStr, "UNDEF");
                break;
            case SYMBOL_INT_ARRAY:
            {
                strcpy(typeStr, "INT_ARRAY");
                strcpy(valueStr, "[");
                for (int j = 0; j < sym->value.int_array.size; j++)
                {
                    char buf[32];
                    sprintf(buf, "%d", sym->value.int_array.array[j]);
                    strcat(valueStr, buf);
                    if (j < sym->value.int_array.size - 1)
                        strcat(valueStr, ", ");
                }
                strcat(valueStr, "]");
                break;
            }
            case SYMBOL_INT_2D_ARRAY:
            {
                strcpy(typeStr, "INT_2D_ARRAY");
                strcpy(valueStr, "[");
                int rows = sym->value.int_2d_arr.size1;
                int cols = sym->value.int_2d_arr.size2;
                for (int r = 0; r < rows; r++)
                {
                    strcat(valueStr, "[");
                    for (int c = 0; c < cols; c++)
                    {
                        char buf[32];
                        sprintf(buf, "%d", sym->value.int_2d_arr.arr[r][c]);
                        strcat(valueStr, buf);
                        if (c < cols - 1)
                            strcat(valueStr, ", ");
                    }
                    strcat(valueStr, "]");
                    if (r < rows - 1)
                        strcat(valueStr, ", ");
                }
                strcat(valueStr, "]");
                break;
            }
            default:
                strcpy(typeStr, "UNKNOWN");
                strcpy(valueStr, "");
                break;
            }
            printf("║ %-*s │ %-*s │ %-*s\n",
                   nameWidth, sym->name,
                   typeWidth, typeStr,
                   valueWidth, valueStr);
        }
    }

    // Bottom border (left border only)
    printf("╚");
    for (int i = 0; i < totalWidth - 1; i++)
        printf("═");
    printf("\n");
}
/* Global declarations instance */
DeclScope *global_decls = NULL;

void initialize_global()
{
    global_decls = (DeclScope *)malloc(sizeof(DeclScope));
    if (!global_decls)
    {
        fprintf(stderr, "Memory allocation failed for global scope\n");
        exit(EXIT_FAILURE);
    }
    global_decls->scope = SCOPE_GLOBAL;

    DeclNode *int_node = (DeclNode *)malloc(sizeof(DeclNode));
    DeclNode *int_array_node = (DeclNode *)malloc(sizeof(DeclNode));
    DeclNode *int_array_2d_node = (DeclNode *)malloc(sizeof(DeclNode));
    DeclNode *float_node = (DeclNode *)malloc(sizeof(DeclNode));

    if (!int_node || !int_array_node || !int_array_2d_node)
    {
        fprintf(stderr, "Memory allocation failed for DeclNodes\n");
        exit(EXIT_FAILURE);
    }

    int_node->type = SYMBOL_INT;
    int_node->type_name = "int";
    int_node->var = NULL;
    int_node->var_count = 0;
    int_node->next = int_array_node;

    int_array_node->type = SYMBOL_INT_ARRAY;
    int_array_node->type_name = "int array";
    int_array_node->var = NULL;
    int_array_node->var_count = 0;
    int_array_node->next = int_array_2d_node;

    int_array_node->type = SYMBOL_INT_2D_ARRAY;
    int_array_node->type_name = "int 2d array";
    int_array_node->var = NULL;
    int_array_node->var_count = 0;
    int_array_node->next = float_node;

    float_node->type = SYMBOL_FLOAT;
    float_node->type_name = "float";
    float_node->var = NULL;
    float_node->var_count = 0;
    float_node->next = NULL;

    global_decls->decl_list = int_node;
}

VariableData *add_var(char *key)
{
    VariableData *newNode = (VariableData *)malloc(sizeof(VariableData));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed for VariableData\n");
        exit(EXIT_FAILURE);
    }
    newNode->type = VARIABLE;
    newNode->data.single.name = key;
    newNode->next = NULL;
    return newNode;
}

VariableData *add_arr(char *key, int size)
{
    VariableData *newNode = (VariableData *)malloc(sizeof(VariableData));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed for VariableData\n");
        exit(EXIT_FAILURE);
    }
    newNode->type = ARRAY;
    newNode->data.array_1d.name = key;
    newNode->data.array_1d.size = size;
    newNode->next = NULL;
    return newNode;
}

VariableData *add_2d_arr(char *key, int size1, int size2)
{
    VariableData *newNode = (VariableData *)malloc(sizeof(VariableData));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed for VariableData\n");
        exit(EXIT_FAILURE);
    }
    newNode->type = ARRAY_2D;
    newNode->data.array_2d.name = key;
    newNode->data.array_2d.size1 = size1;
    newNode->data.array_2d.size2 = size2;
    newNode->next = NULL;
    return newNode;
}

void add_symbols(SymbolType default_type, VariableData *var_list)
{
    if (!global_decls)
    {
        fprintf(stderr, "Global scope not initialized\n");
        return;
    }

    VariableData *current = var_list;
    while (current)
    {
        SymbolType target_type;
        if (current->type == VARIABLE)
        {
            target_type = default_type;
            if (default_type == SYMBOL_INT)
            {
                create_symbol_int(current->data.single.name);
            }
            else if (default_type == SYMBOL_FLOAT)
            {
                create_symbol_float(current->data.single.name);
            }
        }
        else if (current->type == ARRAY)
        {
            target_type = SYMBOL_INT_ARRAY;
            create_symbol_array(current->data.array_1d.name, current->data.array_1d.size);
        }
        else if (current->type == ARRAY_2D)
        {
            target_type = SYMBOL_INT_2D_ARRAY;
            create_symbol_2d_array(current->data.array_2d.name, current->data.array_2d.size1, current->data.array_2d.size2);
        }
        else
        {
            current = current->next;
            continue;
        }

        DeclNode *curr_decl = global_decls->decl_list;
        while (curr_decl && curr_decl->type != target_type)
        {
            curr_decl = curr_decl->next;
        }
        if (!curr_decl)
        {
            fprintf(stderr, "Declaration node for the given type (%d) not found\n", target_type);
            current = current->next;
            continue;
        }
        VariableData **temp = realloc(curr_decl->var, (curr_decl->var_count + 1) * sizeof(VariableData *));
        if (!temp)
        {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        curr_decl->var = temp;
        curr_decl->var[curr_decl->var_count] = current;
        curr_decl->var_count++;

        current = current->next;
    }
}

void print_decls()
{
    if (!global_decls)
    {
        printf("No global declarations.\n");
        return;
    }
    printf("=================================================\n");
    printf("               Global Declarations             \n");
    printf("=================================================\n");
    DeclNode *curr = global_decls->decl_list;
    while (curr)
    {
        if (curr->var_count > 0)
        {
            printf(">> Declarations of type: %s\n", curr->type_name);
            for (int i = 0; i < curr->var_count; i++)
            {
                if (curr->type == SYMBOL_INT || curr->type == SYMBOL_BOOL || curr->type == SYMBOL_FLOAT)
                    printf("    Variable: %s\n", curr->var[i]->data.single.name);
                else if (curr->type == SYMBOL_INT_ARRAY)
                    printf("    Array: %s [%d elements]\n", curr->var[i]->data.array_1d.name, curr->var[i]->data.array_1d.size);
                else if (curr->type == SYMBOL_INT_2D_ARRAY)
                    printf("    Array: %s [%d elements][%d elements]\n", curr->var[i]->data.array_2d.name, curr->var[i]->data.array_2d.size1, curr->var[i]->data.array_2d.size2);
            }
            printf("-------------------------------------------------\n");
        }
        curr = curr->next;
    }
    printf("=================================================\n");
}

void free_decls()
{
    if (!global_decls)
        return;
    DeclNode *curr = global_decls->decl_list;
    while (curr)
    {
        for (int i = 0; i < curr->var_count; i++)
        {
            if (curr->type == SYMBOL_INT)
                free(curr->var[i]->data.single.name);
            else if (curr->type == SYMBOL_INT_ARRAY)
                free(curr->var[i]->data.array_1d.name);
            free(curr->var[i]);
        }
        free(curr->var);
        DeclNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(global_decls);
    global_decls = NULL;
}

/* AST Statement Creation Functions */

Statement *create_statement(StatementType stmt_type, Node *stmt, Statement *next)
{
    Statement *new_stmt = (Statement *)malloc(sizeof(Statement));
    new_stmt->stmt_type = stmt_type;
    new_stmt->stmt = stmt;
    new_stmt->next = next;
    return new_stmt;
}

Statement *create_assign_stmt(Node *var_expr, Node *expr)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_ASSIGN;
    new_node->data.assign.var_expr = var_expr;
    new_node->data.assign.expr = expr;
    return create_statement(STMT_ASSIGN, new_node, NULL);
}

Statement *create_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_FOR;
    new_node->data.for_stmt.init = init;
    new_node->data.for_stmt.cond = cond;
    new_node->data.for_stmt.update = update;
    new_node->data.for_stmt.stmts = stmts;
    return create_statement(STMT_FOR, new_node, NULL);
}

Statement *create_do_while_stmt(Statement *stmts, Node *cond)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_DO_WHILE;
    new_node->data.do_while_stmt.stmts = stmts;
    new_node->data.do_while_stmt.cond = cond;
    return create_statement(STMT_DO_WHILE, new_node, NULL);
}

Statement *create_if_stmt(Node *cond, Statement *if_stmt, Statement *else_stmt)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_IF;
    new_node->data.if_stmt.cond = cond;
    new_node->data.if_stmt.then_stmt = if_stmt;
    new_node->data.if_stmt.else_stmt = else_stmt;
    return create_statement(STMT_IF, new_node, NULL);
}

Statement *create_write_stmt(Node *expr)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_WRITE;
    new_node->data.write.expr = expr;
    return create_statement(STMT_WRITE, new_node, NULL);
}

Statement *create_write_stmt_string(char *str)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_STRING;
    new_node->data.string.str = strdup(str);
    return create_statement(STMT_WRITE, new_node, NULL);
}

Statement *create_break_stmt(void)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_BREAK;
    return create_statement(STMT_BREAK, new_node, NULL);
}

/* AST Node Creation Helper Functions */

Node *create_var_node(char *var)
{
    if (!var || strlen(var) == 0)
    {
        fprintf(stderr, "create_var_node: received an empty identifier!\n");
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_VAR;
    new_node->data.var.var = strdup(var);
    return new_node;
}

Node *create_array_node(char *var, Node *idx_node)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_ARRAY;
    new_node->data.array.var = var;
    new_node->data.array.idx = idx_node;
    return new_node;
}

Node *create_2d_array_node(char *var, Node *idx_node1, Node *idx_node2)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_2D_ARRAY;
    new_node->data.array_2d.var = var;
    new_node->data.array_2d.idx1 = idx_node1;
    new_node->data.array_2d.idx2 = idx_node2;
    return new_node;
}

Node *create_expr_node(OperationType op, Node *left, Node *right)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_EXPR;
    new_node->data.expr.op = op;
    new_node->data.expr.left = left;
    new_node->data.expr.right = right;
    return new_node;
}

Node *create_num_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_NUM;
    new_node->data.num.val = value;
    return new_node;
}

Node *create_float_node(float value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_FLOAT;
    new_node->data.flt.val = value;
    return new_node;
}

Node *create_bool_node(bool boolean)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->nodetype = NODE_BOOL;
    new_node->data.boolean.boolean = boolean;
    return new_node;
}

/* Evaluation Functions */

bool eval_stmts(Statement *stmt)
{
    while (stmt)
    {
        switch (stmt->stmt_type)
        {
        case STMT_ASSIGN:
            eval_assign(stmt->stmt);
            break;
        case STMT_FOR:
            eval_for(stmt->stmt);
            break;
        case STMT_IF:
            eval_if(stmt->stmt);
            break;
        case STMT_WRITE:
            eval_write(stmt->stmt);
            break;
        case STMT_BREAK:
            eval_break(stmt->stmt);
            return true;
        case STMT_DO_WHILE:
            eval_do_while(stmt->stmt);
            break;
        default:
            break;
        }
        if (breakFlag)
        {
            return true;
        }
        stmt = stmt->next;
    }
    return false;
}

void eval_assign(Node *assign_stmt)
{
    Node *var_expr = assign_stmt->data.assign.var_expr;
    Node *expr = assign_stmt->data.assign.expr;
    int val = eval_expr_val(expr);
    switch (var_expr->nodetype)
    {
    case NODE_VAR:
    {
        Symbol *sym = search_symbol(var_expr->data.var.var);
        if (sym->type == SYMBOL_INT)
        {
            if (sym)
            {
                sym->value.int_value.value = val;
                sym->value.int_value.is_defined = true;
            }
        }
        else
        {
            if (sym)
            {
                float val_float = eval_expr_float(expr);
                sym->value.float_value.value = val_float;
                sym->value.float_value.is_defined = true;
            }
        }
        break;
    }
    case NODE_ARRAY:
    {
        Symbol *sym = search_symbol(var_expr->data.array.var);
        if (sym->type == SYMBOL_INT_ARRAY)
        {
            if (sym)
            {
                int index = eval_expr_val(var_expr->data.array.idx);
                sym->value.int_array.array[index] = val;
            }
        }
        else
        {
            fprintf(stderr, "Trying to assign a int value to an array\n");
            exit(EXIT_FAILURE);
        }
        break;
    }
    case NODE_2D_ARRAY:
    {
        Symbol *sym = search_symbol(var_expr->data.array_2d.var);
        if (sym && sym->type == SYMBOL_INT_2D_ARRAY)
        {
            int index1 = eval_expr_val(var_expr->data.array_2d.idx1);
            int index2 = eval_expr_val(var_expr->data.array_2d.idx2);
            if (index1 < 0 || index1 >= sym->value.int_2d_arr.size1 ||
                index2 < 0 || index2 >= sym->value.int_2d_arr.size2)
            {
                fprintf(stderr, "Array out of bounds for %s..!\n", var_expr->data.array_2d.var);
                exit(EXIT_FAILURE);
            }
            sym->value.int_2d_arr.arr[index1][index2] = val;
        }
        else
        {
            fprintf(stderr, "Array %s is not declared or type mismatch!\n", var_expr->data.array_2d.var);
            exit(EXIT_FAILURE);
        }
        break;
    }

    default:
        fprintf(stderr, "Invalid assignment target\n");
        break;
    }
}

int eval_expr_val(Node *expr)
{
    switch (expr->nodetype)
    {
    case NODE_NUM:
        return expr->data.num.val;
    case NODE_EXPR:
    {
        switch (expr->data.expr.op)
        {
        case TOKEN_ADD:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left + right;
        }
        case TOKEN_SUB:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left - right;
        }
        case TOKEN_MUL:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left * right;
        }
        case TOKEN_DIV:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            if (right == 0)
            {
                fprintf(stderr, "Zero Division Error....!\n");
                exit(EXIT_FAILURE);
            }
            return left / right;
        }
        case TOKEN_MOD:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            if (right == 0)
            {
                fprintf(stderr, "Zero Modulus Error....!\n");
                exit(EXIT_FAILURE);
            }
            return left % right;
        }
        default:
            break;
        }
        break;
    }
    case NODE_VAR:
    {
        Symbol *sym = search_symbol(expr->data.var.var);
        if (sym != NULL)
        {
            if (sym->value.int_value.is_defined)
            {
                return sym->value.int_value.value;
            }
            else
            {
                fprintf(stderr, "Variable %s is used before initialization..!\n", expr->data.var.var);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "Variable %s is not declared...!\n", expr->data.var.var);
            exit(EXIT_FAILURE);
        }
    }
    case NODE_ARRAY:
    {
        Symbol *sym = search_symbol(expr->data.array.var);
        if (sym != NULL)
        {
            int index = eval_expr_val(expr->data.array.idx);
            if (index < 0 || index >= sym->value.int_array.size)
            {
                fprintf(stderr, "Array out of bounds for %s..!\n", expr->data.array.var);
                exit(EXIT_FAILURE);
            }
            else
            {
                return sym->value.int_array.array[index];
            }
        }
        else
        {
            fprintf(stderr, "Array %s is not declared...!\n", expr->data.array.var);
            exit(EXIT_FAILURE);
        }
    }
    case NODE_FLOAT:
    {
        return (int)expr->data.flt.val;
    }
    default:
        break;
    }
    return 0;
}

float eval_expr_float(Node *expr)
{
    switch (expr->nodetype)
    {
    case NODE_NUM:
        return (float)expr->data.num.val;
    case NODE_EXPR:
    {
        switch (expr->data.expr.op)
        {
        case TOKEN_ADD:
        {
            float left = eval_expr_float(expr->data.expr.left);
            float right = eval_expr_float(expr->data.expr.right);
            return left + right;
        }
        case TOKEN_SUB:
        {
            float left = eval_expr_float(expr->data.expr.left);
            float right = eval_expr_float(expr->data.expr.right);
            return left - right;
        }
        case TOKEN_MUL:
        {
            float left = eval_expr_float(expr->data.expr.left);
            float right = eval_expr_float(expr->data.expr.right);
            return left * right;
        }
        case TOKEN_DIV:
        {
            float left = eval_expr_float(expr->data.expr.left);
            float right = eval_expr_float(expr->data.expr.right);
            if (right == 0)
            {
                fprintf(stderr, "Zero Division Error....!\n");
                exit(EXIT_FAILURE);
            }
            return left / right;
        }
        case TOKEN_MOD:
        {
            int left = eval_expr_float(expr->data.expr.left);
            int right = eval_expr_float(expr->data.expr.right);
            if (right == 0)
            {
                fprintf(stderr, "Zero Modulus Error....!\n");
                exit(EXIT_FAILURE);
            }
            return left % right;
        }
        }
        break;
    }
    case NODE_VAR:
    {
        Symbol *sym = search_symbol(expr->data.var.var);
        if (sym->type == SYMBOL_INT)
        {
            if (sym != NULL)
            {
                if (sym->value.int_value.is_defined)
                {
                    return (float)sym->value.int_value.value;
                }
                else
                {
                    fprintf(stderr, "Variable %s is used before initialization..!\n", expr->data.var.var);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "Variable %s is not declared...!\n", expr->data.var.var);
                exit(EXIT_FAILURE);
            }
        }
        else if (sym->type == SYMBOL_FLOAT)
        {
            if (sym != NULL)
            {
                if (sym->value.float_value.is_defined)
                {
                    return (float)sym->value.float_value.value;
                }
                else
                {
                    fprintf(stderr, "Variable %s is used before initialization..!\n", expr->data.var.var);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "Variable %s is not declared...!\n", expr->data.var.var);
                exit(EXIT_FAILURE);
            }
        }
    }
    case NODE_ARRAY:
    {
        Symbol *sym = search_symbol(expr->data.array.var);
        if (sym != NULL)
        {
            int index = eval_expr_val(expr->data.array.idx);
            if (index < 0 || index >= sym->value.int_array.size)
            {
                fprintf(stderr, "Array out of bounds for %s..!\n", expr->data.array.var);
                exit(EXIT_FAILURE);
            }
            else
            {
                return (float)sym->value.int_array.array[index];
            }
        }
        else
        {
            fprintf(stderr, "Array %s is not declared...!\n", expr->data.array.var);
            exit(EXIT_FAILURE);
        }
    }
    case NODE_2D_ARRAY:
    {
        Symbol *sym = search_symbol(expr->data.array_2d.var);
        if (sym && sym->type == SYMBOL_INT_2D_ARRAY)
        {
            int index1 = eval_expr_val(expr->data.array_2d.idx1);
            int index2 = eval_expr_val(expr->data.array_2d.idx2);
            if (index1 < 0 || index1 >= sym->value.int_2d_arr.size1 ||
                index2 < 0 || index2 >= sym->value.int_2d_arr.size2)
            {
                fprintf(stderr, "Array out of bounds for %s..!\n", expr->data.array_2d.var);
                exit(EXIT_FAILURE);
            }
            return (float)sym->value.int_2d_arr.arr[index1][index2];
        }
        else
        {
            fprintf(stderr, "Array %s is not declared or type mismatch!\n", expr->data.array_2d.var);
            exit(EXIT_FAILURE);
        }
    }

    case NODE_FLOAT:
    {
        return (float)expr->data.flt.val;
    }
    default:
        break;
    }
    return 0;
}

bool eval_expr_bool(Node *expr)
{
    switch (expr->nodetype)
    {
    case NODE_BOOL:
        return expr->data.boolean.boolean;
    case NODE_EXPR:
    {
        switch (expr->data.expr.op)
        {
        case TOKEN_LT:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left < right;
        }
        case TOKEN_GT:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left > right;
        }
        case TOKEN_GE:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left >= right;
        }
        case TOKEN_LE:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left <= right;
        }
        case TOKEN_NE:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left != right;
        }
        case TOKEN_EQ:
        {
            int left = eval_expr_val(expr->data.expr.left);
            int right = eval_expr_val(expr->data.expr.right);
            return left == right;
        }
        case TOKEN_AND:
        {
            bool left = eval_expr_bool(expr->data.expr.left);
            bool right = eval_expr_bool(expr->data.expr.right);
            return left && right;
        }
        case TOKEN_OR:
        {
            bool left = eval_expr_bool(expr->data.expr.left);
            bool right = eval_expr_bool(expr->data.expr.right);
            return left || right;
        }
        case TOKEN_NOT:
        {
            bool operand = eval_expr_bool(expr->data.expr.right);
            return !operand;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    return false;
}

void eval_do_while(Node *do_while)
{
    Node *cond = do_while->data.do_while_stmt.cond;
    Node *stmts = do_while->data.do_while_stmt.stmts;
    bool breakOccurred = eval_stmts(stmts);
    if (breakOccurred)
    {
        breakFlag = false;
        return;
    }

    while (eval_expr_bool(cond))
    {
        bool breakOccurred = eval_stmts(stmts);
        if (breakOccurred)
        {
            breakFlag = false;
            break;
        }
    }
}

void eval_for(Node *for_stmt)
{
    if (for_stmt->data.for_stmt.init)
    {
        (void)eval_stmts(for_stmt->data.for_stmt.init);
    }
    Node *cond = for_stmt->data.for_stmt.cond;
    Statement *update = for_stmt->data.for_stmt.update;
    Statement *stmts = for_stmt->data.for_stmt.stmts;
    while (eval_expr_bool(cond))
    {
        bool breakOccurred = eval_stmts(stmts);
        if (breakOccurred)
        {
            breakFlag = false;
            break;
        }
        if (update)
        {
            breakOccurred = eval_stmts(update);
            if (breakOccurred)
            {
                breakFlag = false;
                break;
            }
        }
    }
}

void eval_if(Node *if_stmt)
{
    Node *cond = if_stmt->data.if_stmt.cond;
    if (eval_expr_bool(cond))
    {
        Statement *then_stmt = if_stmt->data.if_stmt.then_stmt;
        eval_stmts(then_stmt);
    }
    else
    {
        if (if_stmt->data.if_stmt.else_stmt)
        {
            Statement *else_stmt = if_stmt->data.if_stmt.else_stmt;
            eval_stmts(else_stmt);
        }
    }
}

void eval_write(Node *write_stmt)
{
    switch (write_stmt->nodetype)
    {
    case NODE_STRING:
        printf("%s\n", write_stmt->data.string.str);
        break;
    default:
        float result = eval_expr_float(write_stmt->data.write.expr);
        printf("%.3f\n", result);
        break;
    }
}

void eval_break(Node *break_node)
{
    breakFlag = true;
}

/* Printing Functions */

// Recursively prints the AST node in a tree-like format.
// Recursively prints an AST node and its children in a tree-like format.
void print_node_tree(Node *node, const char *indent) {
    if (!node)
        return;

    // Print the current node type based on its nodetype.
    switch (node->nodetype) {
        case NODE_ASSIGN:
            printf("%s- ASSIGN\n", indent);
            // Print children: left-hand side and right-hand side.
            {
                char childIndent[256];
                snprintf(childIndent, sizeof(childIndent), "%s    ", indent);
                print_node_tree(node->data.assign.var_expr, childIndent);
                print_node_tree(node->data.assign.expr, childIndent);
            }
            break;
        case NODE_VAR:
            printf("%s- VAR\n", indent);
            break;
        case NODE_EXPR:
            // For expressions, print the operator type.
            switch (node->data.expr.op) {
                case TOKEN_ADD: printf("%s- ADD\n", indent); break;
                case TOKEN_SUB: printf("%s- SUB\n", indent); break;
                case TOKEN_MUL: printf("%s- MUL\n", indent); break;
                case TOKEN_DIV: printf("%s- DIV\n", indent); break;
                case TOKEN_MOD: printf("%s- MOD\n", indent); break;
                default:        printf("%s- EXPR\n", indent); break;
            }
            {
                char childIndent[256];
                snprintf(childIndent, sizeof(childIndent), "%s    ", indent);
                print_node_tree(node->data.expr.left, childIndent);
                print_node_tree(node->data.expr.right, childIndent);
            }
            break;
        case NODE_FLOAT:
            printf("%s- FLOAT\n", indent);
            break;
        case NODE_NUM:
            printf("%s- NUM\n", indent);
            break;
        case NODE_ARRAY:
            printf("%s- ARRAY\n", indent);
            {
                char childIndent[256];
                snprintf(childIndent, sizeof(childIndent), "%s    ", indent);
                print_node_tree(node->data.array.idx, childIndent);
            }
            break;
        case NODE_2D_ARRAY:
            printf("%s- 2D_ARRAY\n", indent);
            {
                char childIndent[256];
                snprintf(childIndent, sizeof(childIndent), "%s    ", indent);
                // For 2D arrays, print both indices (if needed) or any extra info.
                print_node_tree(node->data.array_2d.idx1, childIndent);
                print_node_tree(node->data.array_2d.idx2, childIndent);
            }
            break;
        case NODE_DO_WHILE:
            printf("%s- DO_WHILE\n", indent);
            {
                char childIndent[256];
                snprintf(childIndent, sizeof(childIndent), "%s    ", indent);
                printf("%s├── BODY:\n", childIndent);
                // Assume the do–while node contains a field 'stmts' for the loop body.
                print_statements_tree(node->data.do_while_stmt.stmts, childIndent);
                printf("%s└── CONDITION:\n", childIndent);
                print_node_tree(node->data.do_while_stmt.cond, childIndent);
            }
            break;
        default:
            printf("%s- UNKNOWN NODE\n", indent);
            break;
    }
}

// Recursively prints a list of statements in a tree-like format.
void print_statement_tree(Statement *stmt, const char *indent) {
    if (!stmt)
        return;

    // Iterate through the list of statements.
    int count = 0;
    for (Statement *s = stmt; s; s = s->next)
        count++;

    int index = 0;
    for (Statement *s = stmt; s; s = s->next) {
        index++;
        bool isLast = (index == count);
        printf("%s%s", indent, isLast ? "└── " : "├── ");

        // Print a label for the statement type.
        switch (s->stmt_type) {
            case STMT_ASSIGN:
                printf("ASSIGN\n");
                break;
            case STMT_WRITE:
                printf("WRITE\n");
                break;
            case STMT_IF:
                printf("IF\n");
                break;
            case STMT_FOR:
                printf("FOR\n");
                break;
            case STMT_DO_WHILE:
                printf("DO_WHILE\n");
                break;
            case STMT_BREAK:
                printf("BREAK\n");
                break;
            default:
                printf("UNKNOWN STMT\n");
                break;
        }

        // Prepare a new indentation for child nodes.
        char childIndent[256];
        snprintf(childIndent, sizeof(childIndent), "%s%s", indent, isLast ? "    " : "│   ");
        print_node_tree(s->stmt, childIndent);
    }
}

// Helper: For printing statements in a tree-like format.
// (This function is similar to print_statement_tree; adjust the name as needed.)
void print_statements_tree(Statement *stmt, const char *indent) {
    print_statement_tree(stmt, indent);
}

// Top-level function to print all statements with a header.
void print_all_statements_tree(Statement *stmt) {
    printf("========== STATEMENTS ==========\n");
    print_statement_tree(stmt, "");
    printf("================================\n");
}


/* Freeing Functions */

void free_node(Node *node)
{
    if (!node)
        return;
    switch (node->nodetype)
    {
    case NODE_NUM:
        break;
    case NODE_VAR:
        if (node->data.var.var)
            free(node->data.var.var);
        break;
    case NODE_ARRAY:
        free_node(node->data.array.idx);
        break;
    case NODE_EXPR:
        free_node(node->data.expr.left);
        free_node(node->data.expr.right);
        break;
    case NODE_ASSIGN:
        free_node(node->data.assign.var_expr);
        free_node(node->data.assign.expr);
        break;
    case NODE_WRITE:
        free_node(node->data.write.expr);
        break;
    case NODE_IF:
        free_node(node->data.if_stmt.cond);
        free_statements(node->data.if_stmt.then_stmt);
        free_statements(node->data.if_stmt.else_stmt);
        break;
    case NODE_FOR:
        free_statements(node->data.for_stmt.init);
        free_node(node->data.for_stmt.cond);
        free_statements(node->data.for_stmt.update);
        free_statements(node->data.for_stmt.stmts);
        break;
    case NODE_BOOL:
        break;
    case NODE_STRING:
        if (node->data.string.str)
            free(node->data.string.str);
        break;
    default:
        break;
    }
    free(node);
}

void free_statements(Statement *stmt)
{
    while (stmt)
    {
        Statement *next_stmt = stmt->next;
        free_node(stmt->stmt);
        free(stmt);
        stmt = next_stmt;
    }
}
