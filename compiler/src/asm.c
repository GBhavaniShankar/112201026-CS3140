#include "compiler.h"

static FILE *output_file = NULL;
static int if_label_count = 0;
static int for_label_count = 0;

char *get_output_filename(const char *input_path)
{
    char *copy = strdup(input_path);
    char *filename = copy;
    char *last_slash = strrchr(copy, '/');
    if (last_slash)
    {
        filename = last_slash + 1;
    }

    char *last_dot = strrchr(filename, '.');
    if (last_dot)
    {
        *last_dot = '\0';
    }

    char *output = malloc(strlen(filename) + 3);
    sprintf(output, "%s.s", filename);
    free(copy);
    return output;
}

FILE *open_output_file(const char *input_filename)
{
    char *output_filename = get_output_filename(input_filename);
    FILE *file = fopen(output_filename, "w");
    if (!file)
    {
        fprintf(stderr, "Error opening file %s for writing.\n", output_filename);
        exit(EXIT_FAILURE);
    }
    free(output_filename);
    return file;
}

void close_output_file(FILE *file)
{
    if (file)
    {
        fclose(file);
    }
}

void init_code_gen(const char *filename)
{
    output_file = open_output_file(filename);

    char *fname = strrchr(filename, '/');
    if (fname)
    {
        fname++;
    }
    else
    {
        fname = (char *)filename;
    }

    fprintf(output_file,
            "\n\t.file\t1 \"%s\""
            "\n\t.section .mdebug.abi32"
            "\n\t.previous"
            "\n\t.nan\tlegacy"
            "\n\t.module fp=32"
            "\n\t.module nooddspreg"
            "\n\t.abicalls"
            "\n\t.text",
            fname);
}

void generate_main_code()
{
    fprintf(output_file,
            "\n\t.text"
            "\n\t.align\t2"
            "\n\t.globl\tmain"
            "\n\t.set\tnomips16"
            "\n\t.set\tnomicromips"
            "\n\t.ent\tmain"
            "\n\t.type\tmain, @function"
            "\nmain:"
            "\n\t.frame\t$fp,32,$31\t\t# vars= 0, regs= 2/0, args= 16, gp= 8"
            "\n\t.mask\t0xc0000000,-4"
            "\n\t.fmask\t0x00000000,0"
            "\n\t.set\tnoreorder"
            "\n\t.cpload\t$25"
            "\n\t.set\treorder"
            "\n\taddiu\t$sp,$sp,-32"
            "\n\tsw\t$31,28($sp)"
            "\n\tsw\t$fp,24($sp)"
            "\n\tmove\t$fp,$sp"
            "\n\t.cprestore\t16");
}

void generate_end_code()
{
    fprintf(output_file,
            "\n\tmove $2, $0"
            "\n\tmove\t$sp,$fp"
            "\n\tlw\t$31,28($sp)"
            "\n\tlw\t$fp,24($sp)"
            "\n\taddiu\t$sp,$sp,32"
            "\n\tj\t$31"
            "\n\t.end\tmain"
            "\n\t.size\tmain, .-main"
            "\n\t.ident\t\"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0\""
            "\n\t.section\t.note.GNU-stack,\"\",@progbits\n");
}

void generate_vars(Statement *stmts)
{
    fprintf(output_file, "\n# MIPS code for variable declarations");

    Statement *curr = stmts;
    int ct = 0;

    while (curr)
    {
        if (curr->type == STMT_DECL)
        {
            SymbolType type = curr->stmt_data.decl_stmt.type;
            Node *decls = curr->stmt_data.decl_stmt.decls;

            if (type == SYMBOL_INT)
            {
                Node *var = decls;
                while (var)
                {
                    if (var->type == NODE_DECL)
                    {
                        if (var->data.decl.type == VARIABLE)
                        {
                            char *var_name = var->data.decl.decl_var.var.var_name;
                            fprintf(output_file, "\n\t.globl\t%s", var_name);

                            if (!ct)
                            {
                                fprintf(output_file, "\n\t.section\t\t.bss,\"aw\",@nobits");
                                ct = 1;
                            }

                            fprintf(output_file,
                                    "\n\t.align\t2"
                                    "\n\t.type\t%s, @object"
                                    "\n\t.size\t%s, 4"
                                    "\n%s:"
                                    "\n\t.space\t4",
                                    var_name, var_name, var_name);
                        }
                        else if (var->data.decl.type == ARRAY_1D)
                        {
                            char *var_name = var->data.decl.decl_var.arr.var_name;
                            int size = var->data.decl.decl_var.arr.size;
                            int array_size = 4 * size;

                            fprintf(output_file, "\n\t.globl\t%s", var_name);

                            if (!ct)
                            {
                                fprintf(output_file, "\n\t.section\t\t.bss,\"aw\",@nobits");
                                ct = 1;
                            }

                            fprintf(output_file,
                                    "\n\t.align\t2"
                                    "\n\t.type\t%s, @object"
                                    "\n\t.size\t%s, %d"
                                    "\n%s:"
                                    "\n\t.space\t%d",
                                    var_name, var_name, array_size, var_name, array_size);
                        }
                    }
                    var = var->data.decl.next;
                }
            }
        }
        curr = curr->next;
    }

    fprintf(output_file,
            "\n\t.rdata"
            "\n\t.align\t2"
            "\n$LC0:"
            "\n\t.ascii\t\"%%d\\000\""
            "\n\t.align\t2"
            "\n$LC1:"
            "\n\t.ascii\t\"%%d\\n\\000\"");

    generate_main_code();
}

/* Generate code for expressions */
void generate_expr_code(Node *expr)
{
    if (!expr)
        return;

    // Handle unary minus
    if (expr->type == NODE_EXPR && expr->data.expr.op == OP_SUB &&
        ((!expr->data.expr.left && expr->data.expr.right) || (expr->data.expr.left && !expr->data.expr.right)))
    {

        Node *child = expr->data.expr.left ? expr->data.expr.left : expr->data.expr.right;
        generate_expr_code(child);
        fprintf(output_file, "\n\tsubu $2, $zero, $2");
        return;
    }

    // Handle binary operations
    if (expr->type == NODE_EXPR)
    {
        generate_expr_code(expr->data.expr.left);
        fprintf(output_file, "\n\taddiu $sp, $sp, -4");
        fprintf(output_file, "\n\tsw $2, 0($sp)");

        generate_expr_code(expr->data.expr.right);
        fprintf(output_file, "\n\tlw $3, 0($sp)");
        fprintf(output_file, "\n\taddiu $sp, $sp, 4");

        switch (expr->data.expr.op)
        {
        case OP_ADD:
            fprintf(output_file, "\n\taddu $2, $3, $2");
            break;
        case OP_SUB:
            fprintf(output_file, "\n\tsubu $2, $3, $2");
            break;
        case OP_MUL:
            fprintf(output_file, "\n\tmul $2, $3, $2");
            break;
        case OP_DIV:
            fprintf(output_file, "\n\tdiv $3, $2");
            fprintf(output_file, "\n\tmflo $2");
            break;
        case OP_MOD:
            fprintf(output_file, "\n\tdiv $3, $2");
            fprintf(output_file, "\n\tmfhi $2");
            break;
        case OP_AND:
            fprintf(output_file, "\n\tand $2, $3, $2");
            break;
        case OP_OR:
            fprintf(output_file, "\n\tor $2, $3, $2");
            break;
        case OP_EQ:
            fprintf(output_file, "\n\tseq $2, $3, $2");
            break;
        case OP_NE:
            fprintf(output_file, "\n\tsne $2, $3, $2");
            break;
        case OP_LT:
            fprintf(output_file, "\n\tslt $2, $3, $2");
            break;
        case OP_LE:
            fprintf(output_file, "\n\tsle $2, $3, $2");
            break;
        case OP_GT:
            fprintf(output_file, "\n\tsgt $2, $3, $2");
            break;
        case OP_GE:
            fprintf(output_file, "\n\tsge $2, $3, $2");
            break;
        case OP_NEG:
            // This should be handled by the unary condition above
            break;
        }
    }
    // Handle number literals
    else if (expr->type == NODE_NUM)
    {
        fprintf(output_file, "\n\tli $2, %d", expr->data.num.num);
    }
    // Handle boolean literals
    else if (expr->type == NODE_BOOL)
    {
        fprintf(output_file, "\n\tli $2, %d", expr->data.boolean.is_true ? 1 : 0);
    }
    // Handle variables
    else if (expr->type == NODE_VAR)
    {
        char *var_name = expr->data.var.var_name;
        Symbol *sym = search_symbol(var_name);
        if (sym)
        {
            fprintf(output_file, "\n\tla $10, %s", var_name);
            fprintf(output_file, "\n\tlw $2, 0($10)");
        }
        else
        {
            fprintf(stderr, "Error: Undefined variable %s\n", var_name);
            exit(EXIT_FAILURE);
        }
    }
    // Handle array access
    else if (expr->type == NODE_ARR)
    {
        char *var_name = expr->data.arr.var_name;
        Symbol *sym = search_symbol(var_name);
        if (sym)
        {
            fprintf(output_file, "\n\t# Compute index for array access: array[i]");
            generate_expr_code(expr->data.arr.index);
            fprintf(output_file, "\n\tsll $2, $2, 2");
            fprintf(output_file, "\n\tla $10, %s", var_name);
            fprintf(output_file, "\n\tadd $10, $10, $2");
            fprintf(output_file, "\n\tlw $2, 0($10)");
        }
        else
        {
            fprintf(stderr, "Error: Undefined array %s\n", var_name);
            exit(EXIT_FAILURE);
        }
    }
}

/* Generate code for if-else statements */
void generate_if_else_code(Node *cond, Statement *then_stmts, Statement *else_stmts)
{
    int current_label = if_label_count++;

    fprintf(output_file, "\n# MIPS code for IF_ELSE");

    // Generate condition
    generate_expr_code(cond);
    fprintf(output_file, "\n\tbeqz $2, ELSE_LABEL_%d", current_label);

    // Generate then block
    eval_stmts_for_asm(then_stmts);
    fprintf(output_file, "\n\tj END_IF_%d", current_label);

    // Generate else block
    fprintf(output_file, "\nELSE_LABEL_%d:", current_label);
    if (else_stmts)
    {
        eval_stmts_for_asm(else_stmts);
    }

    fprintf(output_file, "\nEND_IF_%d:", current_label);
}

/* Generate code for for statements */
void generate_for_code(Statement *init, Node *cond, Statement *update, Statement *body)
{
    int current_label = for_label_count++;

    fprintf(output_file, "\n# MIPS code for FOR_STMT");

    // Initialization
    if (init)
    {
        eval_stmts_for_asm(init);
    }

    // Start label
    fprintf(output_file, "\nFOR_START_%d:", current_label);

    // Condition
    if (cond)
    {
        generate_expr_code(cond);
        fprintf(output_file, "\n\tbeqz $2, FOR_END_%d", current_label);
    }

    // Loop body
    if (body)
    {
        eval_stmts_for_asm(body);
    }

    // Update
    if (update)
    {
        eval_stmts_for_asm(update);
    }

    fprintf(output_file, "\n\tj FOR_START_%d", current_label);

    // End label
    fprintf(output_file, "\nFOR_END_%d:", current_label);
}

/* Generate code for assignment statements */
void generate_assignment_code(Node *var_expr, Node *expr)
{
    fprintf(output_file, "\n\t# MIPS code for ASSIGNMENT");

    if (!var_expr || !expr)
    {
        fprintf(stderr, "Invalid assignment statement\n");
        return;
    }

    // Generate code for the right-hand side expression
    generate_expr_code(expr);

    // Handle variable assignment
    if (var_expr->type == NODE_VAR)
    {
        char *var_name = var_expr->data.var.var_name;
        Symbol *sym = search_symbol(var_name);
        if (sym)
        {
            fprintf(output_file, "\n\tla $10, %s", var_name);
            fprintf(output_file, "\n\tsw $2, 0($10)");
        }
        else
        {
            fprintf(stderr, "Error: Undefined variable %s\n", var_name);
            exit(EXIT_FAILURE);
        }
    }
    // Handle array assignment
    else if (var_expr->type == NODE_ARR)
    {
        char *var_name = var_expr->data.arr.var_name;
        Symbol *sym = search_symbol(var_name);
        if (sym)
        {
            // Save the RHS value
            fprintf(output_file, "\n\tmove $12, $2");

            // Generate code for the array index
            generate_expr_code(var_expr->data.arr.index);
            fprintf(output_file, "\n\tsll $2, $2, 2");
            fprintf(output_file, "\n\tla $10, %s", var_name);
            fprintf(output_file, "\n\tadd $10, $10, $2");
            fprintf(output_file, "\n\tsw $12, 0($10)");
        }
        else
        {
            fprintf(stderr, "Error: Undefined array %s\n", var_name);
            exit(EXIT_FAILURE);
        }
    }
}

/* Generate code for printf (used in write statements) */
void generate_printf_code(Node *expr)
{
    if (!expr)
        return;

    if (expr->type == NODE_VAR)
    {
        fprintf(output_file, "\n\tla $4, $LC1");
        fprintf(output_file, "\n\tla $8, %s", expr->data.var.var_name);
        fprintf(output_file, "\n\tlw $5, 0($8)");
        fprintf(output_file, "\n\tjal printf");
    }
    else if (expr->type == NODE_ARR)
    {
        fprintf(output_file, "\n\tla $4, $LC1");
        generate_expr_code(expr->data.arr.index);
        fprintf(output_file, "\n\tsll $8, $2, 2");
        fprintf(output_file, "\n\tla $9, %s", expr->data.arr.var_name);
        fprintf(output_file, "\n\taddu $9, $9, $8");
        fprintf(output_file, "\n\tlw $5, 0($9)");
        fprintf(output_file, "\n\tjal printf");
    }
    else if (expr->type == NODE_EXPR)
    {
        fprintf(output_file, "\n\tla $4, $LC1");
        generate_expr_code(expr);
        fprintf(output_file, "\n\tmove $5, $2");
        fprintf(output_file, "\n\tjal printf");
    }
    else if (expr->type == NODE_NUM)
    {
        fprintf(output_file, "\n\tla $4, $LC1");
        fprintf(output_file, "\n\tli $5, %d", expr->data.num.num);
        fprintf(output_file, "\n\tjal printf");
    }
    else if (expr->type == NODE_BOOL)
    {
        fprintf(output_file, "\n\tla $4, $LC1");
        fprintf(output_file, "\n\tli $5, %d", expr->data.boolean.is_true ? 1 : 0);
        fprintf(output_file, "\n\tjal printf");
    }
}

/* Generate code for write statements */
void generate_write_code(bool is_string, Node *expr, char *string)
{
    fprintf(output_file, "\n# MIPS code for WRITE");

    if (is_string)
    {
        // Print string literal - this would require some additional handling
        // For simplicity, we'll just print a newline for now
        fprintf(output_file, "\n\tla $4, $LC1");
        fprintf(output_file, "\n\tli $5, 0");
        fprintf(output_file, "\n\tjal printf");
    }
    else
    {
        generate_printf_code(expr);
    }
}

/* Generate code for scanf (used in read statements) */
void generate_scanf_code(Node *var_expr)
{
    if (!var_expr)
        return;

    if (var_expr->type == NODE_VAR)
    {
        fprintf(output_file, "\n\tla $4, $LC0");
        fprintf(output_file, "\n\tla $5, %s", var_expr->data.var.var_name);
        fprintf(output_file, "\n\tjal __isoc99_scanf");
    }
    else if (var_expr->type == NODE_ARR)
    {
        fprintf(output_file, "\n\tla $4, $LC0");
        generate_expr_code(var_expr->data.arr.index);
        fprintf(output_file, "\n\tsll $8, $2, 2");
        fprintf(output_file, "\n\tla $9, %s", var_expr->data.arr.var_name);
        fprintf(output_file, "\n\taddu $5, $9, $8");
        fprintf(output_file, "\n\tjal __isoc99_scanf");
    }
}

/* Generate code for read statements */
void generate_read_code(Node *var_expr)
{
    fprintf(output_file, "\n# MIPS code for READ");
    generate_scanf_code(var_expr);
}

/* Generate code for break statements */
void generate_break_code()
{
    int current_label = for_label_count - 1;
    fprintf(output_file, "\n# MIPS code for BREAK");
    fprintf(output_file, "\n\tj FOR_END_%d", current_label);
}

/* Evaluate statements and generate code */
void eval_stmts_for_asm(Statement *stmts)
{
    // Use the new code generation functions
    Statement *curr = stmts;

    while (curr)
    {
        switch (curr->type)
        {
        case STMT_ASSIGN:
            generate_assignment_code(curr->stmt_data.assign_stmt.var_expr,
                                     curr->stmt_data.assign_stmt.expr);
            break;
        case STMT_IF:
            generate_if_else_code(curr->stmt_data.if_stmt.cond,
                                  curr->stmt_data.if_stmt.then_stmts,
                                  curr->stmt_data.if_stmt.else_stmts);
            break;
        case STMT_FOR:
            generate_for_code(curr->stmt_data.for_stmt.init_stmt,
                              curr->stmt_data.for_stmt.cond_stmt,
                              curr->stmt_data.for_stmt.update_stmt,
                              curr->stmt_data.for_stmt.stmts);
            break;
        case STMT_WRITE:
            generate_write_code(curr->stmt_data.write_stmt.is_string,
                                curr->stmt_data.write_stmt.is_string ? NULL : curr->stmt_data.write_stmt.write_data.expr,
                                curr->stmt_data.write_stmt.is_string ? curr->stmt_data.write_stmt.write_data.string : NULL);
            break;
        case STMT_READ:
            generate_read_code(curr->stmt_data.read_stmt.var_expr);
            break;
        case STMT_BREAK:
            generate_break_code();
            break;
        case STMT_DECL:
            // Variable declarations are handled in generate_vars
            break;
        default:
            fprintf(stderr, "Unknown statement type\n");
            break;
        }
        curr = curr->next;
    }
}

/* Generate code for the entire program */
void generate_code(Statement *stmts)
{
    // First generate variable declarations
    generate_vars(stmts);

    // Then generate code for the statements
    eval_stmts_for_asm(stmts);

    // Finally, generate the end of the main function
    generate_end_code();

    // Close the output file
    close_output_file(output_file);
}