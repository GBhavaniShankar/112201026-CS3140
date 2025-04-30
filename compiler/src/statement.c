#include "compiler.h"

Statement *global_stmts = NULL;

bool break_occured = false;

SymbolType find_symbol_type(char *key)
{
    Symbol *symbol = search_symbol(key);
    return symbol->type;
}

Node *create_expr_node(OperationType op_type, Node *left, Node *right)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_EXPR;
    newNode->data.expr.op = op_type;
    newNode->data.expr.left = left;
    newNode->data.expr.right = right;
    return newNode;
}

Node *create_num_node(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_NUM;
    newNode->data.num.num = value;
    return newNode;
}

Node *create_bool_node(bool is_true)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_BOOL;
    newNode->data.boolean.is_true = is_true;
    return newNode;
}

Node *create_var_node(char *var_name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_VAR;
    newNode->data.var.var_name = var_name;
    return newNode;
}

Node *create_array_node(char *var_name, Node *index)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_ARR;
    newNode->data.arr.var_name = var_name;
    newNode->data.arr.index = index;
    return newNode;
}

Node *create_var_decl_node(char *var_name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_DECL;
    newNode->data.decl.type = VARIABLE;
    newNode->data.decl.decl_var.var.var_name = var_name;
    newNode->data.decl.next = NULL;
    return newNode;
}

Node *create_arr_decl_node(char *var_name, int size)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->type = NODE_DECL;
    newNode->data.decl.type = ARRAY_1D;
    newNode->data.decl.decl_var.arr.var_name = var_name;
    newNode->data.decl.decl_var.arr.size = size;
    newNode->data.decl.next = NULL;
    return newNode;
}

Statement *create_assign_stmt(Node *var_expr, Node *expr)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_ASSIGN;
    newStatement->stmt_data.assign_stmt.var_expr = var_expr;
    newStatement->stmt_data.assign_stmt.expr = expr;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_FOR;
    newStatement->stmt_data.for_stmt.init_stmt = init;
    newStatement->stmt_data.for_stmt.cond_stmt = cond;
    newStatement->stmt_data.for_stmt.update_stmt = update;
    newStatement->stmt_data.for_stmt.stmts = stmts;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_if_stmt(Node *cond, Statement *then_stmts, Statement *else_stmts)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_IF;
    newStatement->stmt_data.if_stmt.cond = cond;
    newStatement->stmt_data.if_stmt.then_stmts = then_stmts;
    newStatement->stmt_data.if_stmt.else_stmts = else_stmts;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_write_stmt(bool is_str, Node *expr, char *string)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_WRITE;
    if (is_str)
    {
        newStatement->stmt_data.write_stmt.write_data.string = string;
    }
    else
    {
        newStatement->stmt_data.write_stmt.write_data.expr = expr;
    }
    newStatement->stmt_data.write_stmt.is_string = is_str;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_break_stmt()
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_BREAK;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_decl_stmt(SymbolType type, Node *decls)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_DECL;
    newStatement->stmt_data.decl_stmt.type = type;
    newStatement->stmt_data.decl_stmt.decls = decls;
    newStatement->next = NULL;
    return newStatement;
}

Statement *create_read_stmt(Node *var_expr)
{
    Statement *newStatement = (Statement *)malloc(sizeof(Statement));
    newStatement->type = STMT_READ;
    newStatement->stmt_data.read_stmt.var_expr = var_expr;
    newStatement->next = NULL;
    return newStatement;
}

Statement *merge_ast_segments(Statement *gdecls, Statement *ldecls, Statement *mainblock)
{
    Statement *head = NULL, *temp = NULL;

    if (gdecls)
    {
        head = gdecls;
        temp = gdecls;
        while (temp->next)
            temp = temp->next;
        if (ldecls)
        {
            temp->next = ldecls;
            while (temp->next)
                temp = temp->next;
        }
        temp->next = mainblock;
    }
    else if (ldecls)
    {
        head = ldecls;
        temp = ldecls;
        while (temp->next)
            temp = temp->next;
        temp->next = mainblock;
    }
    else
    {
        head = mainblock;
    }

    return head;
}

void eval_stmts(Statement *stmts)
{
    Statement *stmt = stmts;
    while (stmt)
    {
        if (break_occured)
            break;

        switch (stmt->type)
        {
        // case STMT_ASSIGN:
        // {
        //     Node *var_expr = stmt->stmt_data.assign_stmt.var_expr;
        //     Node *expr = stmt->stmt_data.assign_stmt.expr;
        //     eval_assign_stmt(var_expr, expr);
        //     break;
        // }
        // case STMT_FOR:
        // {
        //     Statement *init = stmt->stmt_data.for_stmt.init_stmt;
        //     Node *cond = stmt->stmt_data.for_stmt.cond_stmt;
        //     Statement *update = stmt->stmt_data.for_stmt.update_stmt;
        //     Statement *stmts_to_eval = stmt->stmt_data.for_stmt.stmts;
        //     eval_for_stmt(init, cond, update, stmts_to_eval);
        //     break;
        // }
        // case STMT_IF:
        // {
        //     Node *cond = stmt->stmt_data.if_stmt.cond;
        //     Statement *then_stmts = stmt->stmt_data.if_stmt.then_stmts;
        //     Statement *else_stmts = stmt->stmt_data.if_stmt.else_stmts;
        //     eval_if_stmt(cond, then_stmts, else_stmts);
        //     break;
        // }
        // case STMT_WRITE:
        // {
        //     if (stmt->stmt_data.write_stmt.is_string)
        //     {
        //         char *str = stmt->stmt_data.write_stmt.write_data.string;
        //         eval_write_stmt(true, NULL, str);
        //     }
        //     else
        //     {
        //         Node *expr = stmt->stmt_data.write_stmt.write_data.expr;
        //         eval_write_stmt(false, expr, "");
        //     }
        //     break;
        // }
        // case STMT_BREAK:
        // {
        //     eval_break_stmt();
        //     break;
        // }
        case STMT_DECL:
        {
            SymbolType type = stmt->stmt_data.decl_stmt.type;
            Node *decls = stmt->stmt_data.decl_stmt.decls;
            eval_decl_stmt(type, decls);
            break;
        }
        }
        stmt = stmt->next;
    }
}

int eval_expr_int(Node *expr)
{
    if (!expr)
    {
        fprintf(stderr, "Error: NULL expression passed to eval_expr_int\n");
        exit(EXIT_FAILURE);
    }

    switch (expr->type)
    {
    case NODE_NUM:
        return expr->data.num.num;
    case NODE_VAR:
    {
        if (find_symbol_type(expr->data.var.var_name) != SYMBOL_INT)
        {
            fprintf(stderr, "Error: Variable '%s' is not of integer type.\n", expr->data.var.var_name);
            exit(EXIT_FAILURE);
        }
        return lookup_int(expr->data.var.var_name);
    }
    case NODE_ARR:
    {
        if (find_symbol_type(expr->data.arr.var_name) != SYMBOL_INT_ARRAY)
        {
            fprintf(stderr, "Error: Array '%s' is not of integer array type.\n", expr->data.arr.var_name);
            exit(EXIT_FAILURE);
        }
        int index = eval_expr_int(expr->data.arr.index);
        return lookup_int_arr(expr->data.arr.var_name, index);
    }
    case NODE_EXPR:
    {
        int left_val = eval_expr_int(expr->data.expr.left);
        int right_val = eval_expr_int(expr->data.expr.right);
        switch (expr->data.expr.op)
        {
        case OP_ADD:
            return left_val + right_val;
        case OP_SUB:
            return left_val - right_val;
        case OP_MUL:
            return left_val * right_val;
        case OP_DIV:
            if (right_val != 0)
                return left_val / right_val;
            else
            {
                fprintf(stderr, "Zero Division Error in integer expression!\n");
                exit(EXIT_FAILURE);
            }
        case OP_MOD:
            if (right_val != 0)
                return left_val % right_val;
            else
            {
                fprintf(stderr, "Zero Modulus Error in integer expression!\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Unknown operator in integer expression\n");
            exit(EXIT_FAILURE);
        }
    }
    default:
        fprintf(stderr, "Error: Unknown node type in integer expression\n");
        exit(EXIT_FAILURE);
    }
}

bool eval_expr_bool(Node *expr)
{
    if (expr)
    {
        switch (expr->type)
        {
        case NODE_BOOL:
            return expr->data.boolean.is_true;
        case NODE_EXPR:
        {
            switch (expr->data.expr.op)
            {
            case OP_LT:
            case OP_GT:
            case OP_LE:
            case OP_GE:
            case OP_NE:
            case OP_EQ:
            {
                int left_val = eval_expr_int(expr->data.expr.left);
                int right_val = eval_expr_int(expr->data.expr.right);
                switch (expr->data.expr.op)
                {
                case OP_LT:
                    return left_val < right_val;
                case OP_GT:
                    return left_val > right_val;
                case OP_LE:
                    return left_val <= right_val;
                case OP_GE:
                    return left_val >= right_val;
                case OP_NE:
                    return left_val != right_val;
                case OP_EQ:
                    return left_val == right_val;
                default:
                    break;
                }
                break;
            }
            case OP_AND:
            {
                bool left_bool = eval_expr_bool(expr->data.expr.left);
                bool right_bool = eval_expr_bool(expr->data.expr.right);
                return left_bool && right_bool;
            }
            case OP_OR:
            {
                bool left_bool = eval_expr_bool(expr->data.expr.left);
                bool right_bool = eval_expr_bool(expr->data.expr.right);
                return left_bool || right_bool;
            }
            case OP_NEG:
            {
                bool operand = eval_expr_bool(expr->data.expr.right);
                return !operand;
            }
            default:
                fprintf(stderr, "Unknown operator in boolean expression\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case NODE_NUM:
            fprintf(stderr, "Error in evaluating / assigning the expression due to type conflict...!\n");
            exit(EXIT_FAILURE);
        default:
            return false;
        }
    }
    return false;
}

void eval_assign_stmt(Node *var_expr, Node *expr)
{
    switch (var_expr->type)
    {
    case NODE_VAR:
        switch (find_symbol_type(var_expr->data.var.var_name))
        {
        case SYMBOL_INT:
        {
            if (is_boolean_expr(expr))
            {
                fprintf(stderr, "The expression that evaluetes the value of %s is not of its type...!\n", var_expr->data.var.var_name);
                exit(EXIT_FAILURE);
            }
            else
            {
                int value_int = eval_expr_int(expr);
                update_symbol_int(var_expr->data.var.var_name, value_int);
            }
            break;
        }
        default:
            fprintf(stderr, "Error: Incompatible type in assignment for variable '%s'.\n", var_expr->data.var.var_name);
            exit(EXIT_FAILURE);
        }
        break;
    case NODE_ARR:
    {
        int index = eval_expr_int(var_expr->data.arr.index);
        switch (find_symbol_type(var_expr->data.arr.var_name))
        {
        case SYMBOL_INT_ARRAY:
        {
            int value_arr_int = eval_expr_int(expr);
            update_symbol_int_array(var_expr->data.arr.var_name, index, value_arr_int);
            break;
        }
        default:
            fprintf(stderr, "Error: Incompatible type in assignment for array '%s'.\n", var_expr->data.arr.var_name);
            exit(EXIT_FAILURE);
        }
        break;
    }
    default:
        fprintf(stderr, "Error: Invalid left-hand side in assignment.\n");
        exit(EXIT_FAILURE);
    }
}

void eval_if_stmt(Node *cond, Statement *then_stmts, Statement *else_stmts)
{
    if (eval_expr_bool(cond))
    {
        eval_stmts(then_stmts);
    }
    else
    {
        eval_stmts(else_stmts);
    }
}

void eval_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts)
{
    if (init)
    {
        eval_stmts(init);
    }
    while (eval_expr_bool(cond))
    {
        eval_stmts(stmts);
        if (break_occured)
        {
            break_occured = false;
            break;
        }
        if (update)
        {
            eval_stmts(update);
        }
    }
}

bool is_boolean_expr(Node *expr)
{
    if (!expr)
        return false;
    switch (expr->type)
    {
    case NODE_BOOL:
        return true;
    case NODE_EXPR:
    {
        OperationType op = expr->data.expr.op;
        switch (op)
        {
        case OP_LT:
        case OP_GT:
        case OP_LE:
        case OP_GE:
        case OP_NE:
        case OP_EQ:
        case OP_AND:
        case OP_OR:
        case OP_NEG:
            return true;
        default:
            return false;
        }
    }
    default:
        return false;
    }
}

void eval_write_stmt(bool is_str, Node *expr, char *string)
{
    if (is_str)
    {
        printf("%s\n", string);
    }
    else
    {
        if (!expr)
        {
            printf("\n");
        }

        if (is_boolean_expr(expr))
        {
            bool b = eval_expr_bool(expr);
            printf("%s\n", b ? "true" : "false");
        }
        else
        {
            int v = eval_expr_int(expr);
            printf("%d\n", v);
        }
    }
}

void eval_break_stmt()
{
    break_occured = true;
}

void eval_decl_stmt(SymbolType type, Node *decls)
{
    Node *decl = decls;
    while (decl)
    {
        ValueType val_type = decl->data.decl.type;
        switch (type)
        {
        case SYMBOL_INT:
            switch (val_type)
            {
            case VARIABLE:
            {
                char *var_name = decl->data.decl.decl_var.var.var_name;
                create_symbol_int(var_name);
                break;
            }
            case ARRAY_1D:
            {
                char *arr_name = decl->data.decl.decl_var.arr.var_name;
                int size = decl->data.decl.decl_var.arr.size;
                create_symbol_int_array(arr_name, size);
                break;
            }
            }
            break;
        }
        decl = decl->data.decl.next;
    }
}

void free_expr(Node *expr)
{
    if (!expr)
        return;

    switch (expr->type)
    {
    case NODE_EXPR:
        free_expr(expr->data.expr.left);
        free_expr(expr->data.expr.right);
        break;
    case NODE_ARR:
        free_expr(expr->data.arr.index);
        break;
    case NODE_VAR:
        break;
    case NODE_NUM:
    case NODE_BOOL:
        break;
    }
    free(expr);
}

void free_decl(Node *decl)
{
    while (decl)
    {
        if (decl->data.decl.type == VARIABLE)
        {
            free(decl->data.decl.decl_var.var.var_name);
        }
        else if (decl->data.decl.type == ARRAY_1D)
        {
            free(decl->data.decl.decl_var.arr.var_name);
        }
        Node *next_decl = decl->data.decl.next;
        free(decl);
        decl = next_decl;
    }
}

void free_statement_rec(Statement *stmt)
{
    if (!stmt)
        return;

    switch (stmt->type)
    {
    case STMT_ASSIGN:
        free_expr(stmt->stmt_data.assign_stmt.var_expr);
        free_expr(stmt->stmt_data.assign_stmt.expr);
        break;
    case STMT_FOR:
        free_statement_rec(stmt->stmt_data.for_stmt.init_stmt);
        free_expr(stmt->stmt_data.for_stmt.cond_stmt);
        free_statement_rec(stmt->stmt_data.for_stmt.update_stmt);
        free_statement_rec(stmt->stmt_data.for_stmt.stmts);
        break;
    case STMT_IF:
        free_expr(stmt->stmt_data.if_stmt.cond);
        free_statement_rec(stmt->stmt_data.if_stmt.then_stmts);
        free_statement_rec(stmt->stmt_data.if_stmt.else_stmts);
        break;
    case STMT_WRITE:
        if (!stmt->stmt_data.write_stmt.is_string)
            free_expr(stmt->stmt_data.write_stmt.write_data.expr);
        break;
    case STMT_BREAK:
        break;
    case STMT_DECL:
        free_decl(stmt->stmt_data.decl_stmt.decls);
    }

    free_statement_rec(stmt->next);
    free(stmt);
}

void free_statements()
{
    free_statement_rec(global_stmts);
    global_stmts = NULL;
}

static const char *op_to_string(OperationType op)
{
    switch (op)
    {
    case OP_ADD:
        return "+";
    case OP_SUB:
        return "-";
    case OP_MUL:
        return "*";
    case OP_DIV:
        return "/";
    case OP_MOD:
        return "%";
    case OP_LT:
        return "<";
    case OP_GT:
        return ">";
    case OP_LE:
        return "<=";
    case OP_GE:
        return ">=";
    case OP_NE:
        return "!=";
    case OP_EQ:
        return "==";
    case OP_AND:
        return "&&";
    case OP_OR:
        return "||";
    case OP_NEG:
        return "!";
    default:
        return "?";
    }
}

// Helper to print the branch prefix.
// It prints the accumulated prefix and then the branch connector.
void print_tree_prefix(const char *prefix, bool isLast)
{
    printf("%s", prefix);
    if (isLast)
        printf("└── ");
    else
        printf("├── ");
}

// Recursive function to print an expression node in tree style.
void print_ast_expr(Node *expr, const char *prefix, bool isLast)
{
    char newPrefix[256];
    if (!expr)
    {
        print_tree_prefix(prefix, isLast);
        printf(RED "NULL" RESET "\n");
        return;
    }

    switch (expr->type)
    {
    case NODE_NUM:
        print_tree_prefix(prefix, isLast);
        printf("Number: " YELLOW "%d" RESET "\n", expr->data.num.num);
        break;
    case NODE_BOOL:
        print_tree_prefix(prefix, isLast);
        printf("Boolean: " MAGENTA "%s" RESET "\n", expr->data.boolean.is_true ? "true" : "false");
        break;
    case NODE_VAR:
        print_tree_prefix(prefix, isLast);
        printf("Variable: " CYAN "%s" RESET "\n", expr->data.var.var_name);
        break;
    case NODE_ARR:
        print_tree_prefix(prefix, isLast);
        printf("Array Access: " CYAN "%s" RESET "\n", expr->data.arr.var_name);
        // Update prefix for the child.
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        print_ast_expr(expr->data.arr.index, newPrefix, true);
        break;
    case NODE_EXPR:
        print_tree_prefix(prefix, isLast);
        printf("Expression\n");
        // Update prefix for children.
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        // Left child.
        print_ast_expr(expr->data.expr.left, newPrefix, false);
        // Operator as a separate branch.
        print_tree_prefix(newPrefix, false);
        printf("Operator: " GREEN "%s" RESET "\n", op_to_string(expr->data.expr.op));
        // Right child.
        print_ast_expr(expr->data.expr.right, newPrefix, true);
        break;

        break;
    default:
        print_tree_prefix(prefix, isLast);
        printf(RED "UnknownExpr" RESET "\n");
        break;
    }
}

// Recursive function to print a statement node in tree style.
void print_ast_stmt(Statement *stmt, const char *prefix, bool isLast)
{
    char newPrefix[256];
    if (!stmt)
        return;

    switch (stmt->type)
    {
    case STMT_ASSIGN:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "Assign" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        // LHS.
        print_tree_prefix(newPrefix, false);
        printf("LHS:\n");
        print_ast_expr(stmt->stmt_data.assign_stmt.var_expr, newPrefix, false);
        // RHS.
        print_tree_prefix(newPrefix, true);
        printf("RHS:\n");
        print_ast_expr(stmt->stmt_data.assign_stmt.expr, newPrefix, true);
        break;
    case STMT_FOR:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "For Loop" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        // Initialization.
        print_tree_prefix(newPrefix, false);
        printf("Init:\n");
        if (stmt->stmt_data.for_stmt.init_stmt)
            ; // Print the list below.
        // We'll print the list of init statements.
        // Condition.
        if (stmt->stmt_data.for_stmt.init_stmt)
            print_ast_stmt_list(stmt->stmt_data.for_stmt.init_stmt, newPrefix);
        print_tree_prefix(newPrefix, false);
        printf("Condition:\n");
        print_ast_expr(stmt->stmt_data.for_stmt.cond_stmt, newPrefix, true);
        // Update.
        print_tree_prefix(newPrefix, false);
        printf("Update:\n");
        if (stmt->stmt_data.for_stmt.update_stmt)
            ; // Print the list below.
        if (stmt->stmt_data.for_stmt.update_stmt)
            print_ast_stmt_list(stmt->stmt_data.for_stmt.update_stmt, newPrefix);
        // Body.
        print_tree_prefix(newPrefix, true);
        printf("Body:\n");
        if (stmt->stmt_data.for_stmt.stmts)
            ; // Print the list below.
        // For lists, we'll use the helper function below.
        if (stmt->stmt_data.for_stmt.stmts)
            print_ast_stmt_list(stmt->stmt_data.for_stmt.stmts, newPrefix);
        break;
    case STMT_IF:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "If Statement" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        // Condition.
        print_tree_prefix(newPrefix, false);
        printf("Condition:\n");
        print_ast_expr(stmt->stmt_data.if_stmt.cond, newPrefix, true);
        // Then branch.
        print_tree_prefix(newPrefix, false);
        printf("Then:\n");
        if (stmt->stmt_data.if_stmt.then_stmts)
            print_ast_stmt_list(stmt->stmt_data.if_stmt.then_stmts, newPrefix);
        // Else branch.
        if (stmt->stmt_data.if_stmt.else_stmts)
        {
            print_tree_prefix(newPrefix, true);
            printf("Else:\n");
            print_ast_stmt_list(stmt->stmt_data.if_stmt.else_stmts, newPrefix);
        }
        break;
    case STMT_WRITE:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "Write" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        if (stmt->stmt_data.write_stmt.is_string)
        {
            print_tree_prefix(newPrefix, true);
            printf("String: " MAGENTA "\"%s\"" RESET "\n", stmt->stmt_data.write_stmt.write_data.string);
        }
        else
        {
            print_tree_prefix(newPrefix, true);
            printf("Expr:\n");
            print_ast_expr(stmt->stmt_data.write_stmt.write_data.expr, newPrefix, true);
        }
        break;
    case STMT_READ:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "Read" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        print_ast_expr(stmt->stmt_data.read_stmt.var_expr, newPrefix, true);
        break;
    case STMT_BREAK:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "Break" RESET "\n");
        break;
    case STMT_DECL:
        print_tree_prefix(prefix, isLast);
        printf(BLUE "Declaration" RESET "\n");
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "│   ");
        {
            Node *decl = stmt->stmt_data.decl_stmt.decls;
            // Print each declaration in the merged chain.
            while (decl)
            {
                print_tree_prefix(newPrefix, true);
                if (decl->data.decl.type == VARIABLE)
                {
                    printf("Variable Declaration: " CYAN "%s" RESET "\n",
                           decl->data.decl.decl_var.var.var_name);
                }
                else if (decl->data.decl.type == ARRAY_1D)
                {
                    printf("Array Declaration: " CYAN "%s" RESET " (size: " YELLOW "%d" RESET ")\n",
                           decl->data.decl.decl_var.arr.var_name,
                           decl->data.decl.decl_var.arr.size);
                }
                decl = decl->data.decl.next;
            }
        }
        break;
    default:
        print_tree_prefix(prefix, isLast);
        printf(RED "Unknown Statement" RESET "\n");
        break;
    }
}

// Helper to print a list of statements in tree style.
// It calculates which statement is the last in the list to set branch connectors appropriately.
void print_ast_stmt_list(Statement *stmts, const char *prefix)
{
    // First, count the statements.
    int count = 0;
    for (Statement *temp = stmts; temp; temp = temp->next)
        count++;

    int index = 0;
    for (Statement *temp = stmts; temp; temp = temp->next, index++)
    {
        bool isLast = (index == count - 1);
        print_ast_stmt(temp, prefix, isLast);
    }
}

// Prints the entire AST (global_stmts) in a tree-like format.
void print_ast()
{
    if (!global_stmts)
    {
        printf(RED "No statements to print.\n" RESET);
        return;
    }
    printf("\n" CYAN BOLD "Abstract Syntax Tree:" RESET "\n");
    print_ast_stmt_list(global_stmts, "");
}