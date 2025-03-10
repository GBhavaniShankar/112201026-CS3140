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

void create_symbol_int(const char *key, int value, bool is_defined)
{
    unsigned int index = hash(key);
    Symbol *new_symbol = create_symbol(key, SYMBOL_INT);
    new_symbol->value.int_value.value = value;
    new_symbol->value.int_value.is_defined = is_defined;
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
    const int tableWidth = 75;
    const char *title = "SYMBOL TABLE";
    int titleLen = strlen(title);
    int leftPadding = (tableWidth - titleLen) / 2;
    for (int i = 0; i < leftPadding; i++)
        printf(" ");
    printf("%s\n", title);
    printf("╔════════════╦════════════╦═══════════════════════════════════════════════╗\n");
    printf("║ %-10s ║ %-10s ║ %-45s ║\n", "Name", "Type", "Value");
    printf("╠════════════╬════════════╬═══════════════════════════════════════════════╣\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Symbol *sym = symbol_table[i];
        while (sym)
        {
            char typeStr[16] = {0};
            char valueStr[64] = {0};
            if (sym->type == SYMBOL_INT)
            {
                strcpy(typeStr, "INT");
                if (sym->value.int_value.is_defined)
                    sprintf(valueStr, "%d", sym->value.int_value.value);
                else
                    strcpy(valueStr, "UNDEF");
            }
            else if (sym->type == SYMBOL_INT_ARRAY)
            {
                strcpy(typeStr, "INT_ARRAY");
                char arrayBuffer[256] = {0};
                int offset = 0;
                offset += sprintf(arrayBuffer + offset, "[");
                int count = sym->value.int_array.size;
                int displayCount = (count > 10) ? 10 : count;
                for (int j = 0; j < displayCount; j++)
                {
                    offset += sprintf(arrayBuffer + offset, "%d", sym->value.int_array.array[j]);
                    if (j < displayCount - 1)
                        offset += sprintf(arrayBuffer + offset, ", ");
                }
                if (count > 10)
                    offset += sprintf(arrayBuffer + offset, "...");
                offset += sprintf(arrayBuffer + offset, "]");
                strncpy(valueStr, arrayBuffer, sizeof(valueStr) - 1);
            }
            printf("║ %-10s ║ %-10s ║ %-45s ║\n", sym->name, typeStr, valueStr);
            sym = sym->next;
        }
    }
    printf("╚════════════╩════════════╩═══════════════════════════════════════════════╝\n");
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
    DeclNode *bool_node = (DeclNode *)malloc(sizeof(DeclNode));
    if (!int_node || !int_array_node || !bool_node)
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
    int_array_node->next = bool_node;

    bool_node->type = SYMBOL_BOOL;
    bool_node->type_name = "bool";
    bool_node->var = NULL;
    bool_node->var_count = 0;
    bool_node->next = NULL;

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
    newNode->data.array.name = key;
    newNode->data.array.size = size;
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
        }
        else if (current->type == ARRAY)
        {
            target_type = SYMBOL_INT_ARRAY;
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
                if (curr->type == SYMBOL_INT || curr->type == SYMBOL_BOOL)
                    printf("    Variable: %s\n", curr->var[i]->data.single.name);
                else if (curr->type == SYMBOL_INT_ARRAY)
                    printf("    Array: %s [%d elements]\n", curr->var[i]->data.array.name, curr->var[i]->data.array.size);
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
                free(curr->var[i]->data.array.name);
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
        if (sym)
        {
            sym->value.int_value.value = val;
            sym->value.int_value.is_defined = true;
        }
        break;
    }
    case NODE_ARRAY:
    {
        Symbol *sym = search_symbol(var_expr->data.array.var);
        if (sym)
        {
            int index = eval_expr_val(var_expr->data.array.idx);
            sym->value.int_array.array[index] = val;
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
    case NODE_EXPR:
    {
        int result = eval_expr_val(write_stmt->data.write.expr);
        printf("%d\n", result);
        break;
    }
    default:
        break;
    }
}

void eval_break(Node *break_node)
{
    breakFlag = true;
}

/* Printing Functions */

void print_prefix(const char *prefix)
{
    printf("%s", prefix);
}

void make_child_prefix(const char *parentPrefix, bool isLast, char *childPrefix, size_t size)
{
    strncpy(childPrefix, parentPrefix, size - 1);
    childPrefix[size - 1] = '\0';
    if (isLast)
        strncat(childPrefix, "    ", size - strlen(childPrefix) - 1);
    else
        strncat(childPrefix, "│   ", size - strlen(childPrefix) - 1);
}

void print_node(Node *node, const char *prefix, bool isLast)
{
    if (!node)
        return;
    printf("%s", prefix);
    if (isLast)
        printf("└── ");
    else
        printf("├── ");
    switch (node->nodetype)
    {
    case NODE_NUM:
        printf("NUM: %d\n", node->data.num.val);
        break;
    case NODE_VAR:
        printf("VAR: %s\n", node->data.var.var);
        break;
    case NODE_ARRAY:
        printf("ARRAY: %s\n", node->data.array.var);
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            print_node(node->data.array.idx, childPrefix, true);
        }
        break;
    case NODE_EXPR:
    {
        char opStr[10] = {0};
        switch (node->data.expr.op)
        {
        case TOKEN_ADD:
            strcpy(opStr, "+");
            break;
        case TOKEN_SUB:
            strcpy(opStr, "-");
            break;
        case TOKEN_MUL:
            strcpy(opStr, "*");
            break;
        case TOKEN_DIV:
            strcpy(opStr, "/");
            break;
        case TOKEN_MOD:
            strcpy(opStr, "%");
            break;
        case TOKEN_LT:
            strcpy(opStr, "<");
            break;
        case TOKEN_GT:
            strcpy(opStr, ">");
            break;
        case TOKEN_GE:
            strcpy(opStr, ">=");
            break;
        case TOKEN_LE:
            strcpy(opStr, "<=");
            break;
        case TOKEN_NE:
            strcpy(opStr, "!=");
            break;
        case TOKEN_EQ:
            strcpy(opStr, "==");
            break;
        case TOKEN_AND:
            strcpy(opStr, "AND");
            break;
        case TOKEN_OR:
            strcpy(opStr, "OR");
            break;
        case TOKEN_NOT:
            strcpy(opStr, "NOT");
            break;
        default:
            break;
        }
        printf("EXPR: %s\n", opStr);
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            print_node(node->data.expr.left, childPrefix, false);
            print_node(node->data.expr.right, childPrefix, true);
        }
        break;
    }
    case NODE_ASSIGN:
        printf("ASSIGNMENT\n");
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            printf("%s├── LHS:\n", childPrefix);
            print_node(node->data.assign.var_expr, childPrefix, false);
            printf("%s└── RHS:\n", childPrefix);
            print_node(node->data.assign.expr, childPrefix, true);
        }
        break;
    case NODE_WRITE:
        printf("WRITE\n");
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            print_node(node->data.write.expr, childPrefix, true);
        }
        break;
    case NODE_IF:
        printf("IF STATEMENT\n");
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            printf("%s├── CONDITION:\n", childPrefix);
            print_node(node->data.if_stmt.cond, childPrefix, false);
            printf("%s├── THEN:\n", childPrefix);
            print_statements(node->data.if_stmt.then_stmt, childPrefix);
            if (node->data.if_stmt.else_stmt)
            {
                printf("%s└── ELSE:\n", childPrefix);
                print_statements(node->data.if_stmt.else_stmt, childPrefix);
            }
        }
        break;
    case NODE_FOR:
        printf("FOR LOOP\n");
        {
            char childPrefix[256];
            make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
            printf("%s├── INIT:\n", childPrefix);
            print_statements(node->data.for_stmt.init, childPrefix);
            printf("%s├── CONDITION:\n", childPrefix);
            print_node(node->data.for_stmt.cond, childPrefix, false);
            printf("%s├── UPDATE:\n", childPrefix);
            print_statements(node->data.for_stmt.update, childPrefix);
            printf("%s└── BODY:\n", childPrefix);
            print_statements(node->data.for_stmt.stmts, childPrefix);
        }
        break;
    case NODE_BOOL:
        printf("BOOL: %s\n", node->data.boolean.boolean ? "true" : "false");
        break;
    case NODE_STRING:
        printf("STRING: \"%s\"\n", node->data.string.str);
        break;
    case NODE_BREAK:
        printf("BREAK\n");
        break;
    default:
        printf("UNKNOWN NODE TYPE\n");
        break;
    }
}

void print_statements(Statement *stmt, const char *prefix)
{
    Statement *s = stmt;
    if (!s)
        return;
    int total = 0;
    for (Statement *temp = s; temp; temp = temp->next)
        total++;
    int index = 0;
    for (; s != NULL; s = s->next)
    {
        index++;
        bool isLast = (index == total);
        printf("%s", prefix);
        if (isLast)
            printf("└── ");
        else
            printf("├── ");
        switch (s->stmt_type)
        {
        case STMT_ASSIGN:
            printf("ASSIGNMENT\n");
            break;
        case STMT_WRITE:
            printf("WRITE\n");
            break;
        case STMT_IF:
            printf("IF STATEMENT\n");
            break;
        case STMT_FOR:
            printf("FOR LOOP\n");
            break;
        case STMT_BREAK:
            printf("BREAK STATEMENT\n");
            break;
        default:
            printf("UNKNOWN STATEMENT\n");
            break;
        }
        char childPrefix[256];
        make_child_prefix(prefix, isLast, childPrefix, sizeof(childPrefix));
        print_node(s->stmt, childPrefix, true);
    }
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
