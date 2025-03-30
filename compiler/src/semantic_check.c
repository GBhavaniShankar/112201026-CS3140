#include "compiler.h"

extern Statement *global_stmts;

ValueType semantic_check_expr(Node *expr)
{
}

void semantic_check_stmts(Statement *stmts)
{
    Statement *stmt = stmts;
    while (stmt)
    {
        switch (stmt->type)
        {
        case STMT_ASSIGN:
        {
            Node *var_expr = stmt->stmt_data.assign_stmt.var_expr;
            Node *expr = stmt->stmt_data.assign_stmt.expr;
            semantic_check_assign(var_expr, expr);
            break;
        }
        case STMT_IF:
        {
            Node *cond = stmt->stmt_data.if_stmt.cond;
            Statement *then_stmt = stmt->stmt_data.if_stmt.then_stmts;
            Statement *else_stmt = stmt->stmt_data.if_stmt.else_stmts;
            semantic_check_if(cond, then_stmt, else_stmt);
            break;
        }
        case STMT_FOR:
        {
            Node *cond = stmt->stmt_data.for_stmt.cond_stmt;
            Statement *init = stmt->stmt_data.for_stmt.init_stmt;
            Statement *update = stmt->stmt_data.for_stmt.update_stmt;
            Statement *stmt_list = stmt->stmt_data.for_stmt.stmts;
            semantic_check_for(init, cond, update, stmt_list);
            break;
        }
        case STMT_WRITE:
        {
            bool is_string = stmt->stmt_data.write_stmt.is_string;
            if (!is_string)
            {
                Node *expr = stmt->stmt_data.write_stmt.write_data.expr;
                semantic_check_write(expr);
            }
            break;
        }
        case STMT_READ:
        {
            Node *var_expr = stmt->stmt_data.read_stmt.var_expr;
            semantic_check_read(var_expr);
            break;
        }
        }
        stmt = stmt->next;
    }
}