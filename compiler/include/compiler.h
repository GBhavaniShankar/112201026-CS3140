#ifndef COMPILER_H
#define COMPILER_H

/**
 * @file compiler.h
 * @brief Header file for SIL Compiler.
 *
 * This file contains declarations for the symbol table, AST (Abstract Syntax Tree)
 * node structures, statement structures, and function prototypes used throughout the
 * SIL Compiler. It also defines various color macros for console output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Macros for symbol table size and terminal colors */
#define TABLE_SIZE 10

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

/* ------------------------------------------------------------------------- */
/*                             Symbol Table                                  */
/* ------------------------------------------------------------------------- */

/**
 * @enum SymbolType
 * @brief Enumeration of possible symbol types.
 */
typedef enum
{
    SYMBOL_INT,      /**< Integer variable symbol. */
    SYMBOL_INT_ARRAY /**< Integer array symbol. */
} SymbolType;

/**
 * @union SymbolValue
 * @brief Union for storing the value of a symbol.
 */
typedef union
{
    struct
    {
        int value;       /**< Value for an integer variable. */
        bool is_defined; /**< Flag indicating if the variable is defined. */
    } int_value;
    struct
    {
        int *array; /**< Pointer to the integer array. */
        int size;   /**< Size of the integer array. */
    } int_array;
} SymbolValue;

/**
 * @struct Symbol
 * @brief Structure representing an entry in the symbol table.
 */
typedef struct Symbol
{
    char *name;          /**< Identifier name. */
    SymbolType type;     /**< Type of the symbol. */
    SymbolValue value;   /**< Value of the symbol. */
    struct Symbol *next; /**< Pointer to the next symbol in the chain (for collision resolution). */
} Symbol;

extern Symbol *symbol_table[TABLE_SIZE];

/**
 * @brief Initializes the symbol table by setting all entries to NULL.
 */
void init_symbol_table();

/**
 * @brief Computes the hash value for a given key.
 * @param key The string key.
 * @return The computed hash value modulo TABLE_SIZE.
 */
unsigned int hash(const char *key);

/**
 * @brief Creates a new symbol with the specified key and adds it to the symbol table.
 * @param key The identifier name.
 * @return Pointer to the newly created symbol.
 */
Symbol *create_symbol(const char *key);

/**
 * @brief Creates a new integer symbol.
 * @param key The identifier name.
 */
void create_symbol_int(const char *key);

/**
 * @brief Creates a new integer array symbol.
 * @param key The identifier name.
 * @param size The size of the array.
 */
void create_symbol_int_array(const char *key, int size);

/**
 * @brief Searches for a symbol by key.
 * @param key The identifier name.
 * @return Pointer to the symbol if found; otherwise, NULL.
 */
Symbol *search_symbol(const char *key);

/**
 * @brief Searches symbol type by key.
 * @param key The identifier name.
 * @return type of that identifier.
 */
SymbolType find_symbol_type(char *key);

/**
 * @brief Updates the value of an integer symbol.
 * @param key The identifier name.
 * @param value The new value.
 */
void update_symbol_int(const char *key, int value);

/**
 * @brief Updates the value at a given index in an integer array symbol.
 * @param key The identifier name.
 * @param index The index to update.
 * @param value The new value.
 */
void update_symbol_int_array(const char *key, int index, int value);

/**
 * @brief Retrieves the integer value of a symbol.
 * @param key The identifier name.
 * @return The integer value.
 */
int lookup_int(const char *key);

/**
 * @brief Retrieves the integer value from an array symbol at a specific index.
 * @param key The identifier name.
 * @param index The index to lookup.
 * @return The integer value at the specified index.
 */
int lookup_int_arr(const char *key, int index);

/**
 * @brief Frees memory associated with a symbol.
 * @param symbol Pointer to the symbol to free.
 */
void free_symbol(Symbol *symbol);

/**
 * @brief Frees the entire symbol table.
 */
void free_symbol_table();

/**
 * @brief Prints the symbol table to the console.
 */
void print_symbol_table();

/**
 * @brief Prints a newline.
 */
static inline void endl() { printf("\n"); }

/* ------------------------------------------------------------------------- */
/*                             AST and Statements                          */
/* ------------------------------------------------------------------------- */

/**
 * @enum ValueType
 * @brief Enumeration of variable declaration types.
 */
typedef enum
{
    VARIABLE, /**< Single variable declaration. */
    ARRAY_1D  /**< One-dimensional array declaration. */
} ValueType;

/**
 * @enum StatementType
 * @brief Enumeration of possible statement types in the AST.
 */
typedef enum
{
    STMT_FOR,    /**< For loop statement. */
    STMT_IF,     /**< If statement. */
    STMT_WRITE,  /**< Write (output) statement. */
    STMT_ASSIGN, /**< Assignment statement. */
    STMT_BREAK,  /**< Break statement. */
    STMT_DECL    /**< Declaration statement. */
} StatementType;

/**
 * @enum NodeType
 * @brief Enumeration of possible AST node types.
 */
typedef enum
{
    NODE_EXPR, /**< Expression node. */
    NODE_NUM,  /**< Numeric constant node. */
    NODE_VAR,  /**< Variable node. */
    NODE_ARR,  /**< Array access node. */
    NODE_BOOL, /**< Boolean constant node. */
    NODE_DECL  /**< Declaration node (used in STMT_DECL). */
} NodeType;

/**
 * @enum OperationType
 * @brief Enumeration of possible operations in expression nodes.
 */
typedef enum
{
    OP_ADD, /**< Addition operator. */
    OP_SUB, /**< Subtraction operator. */
    OP_MUL, /**< Multiplication operator. */
    OP_DIV, /**< Division operator. */
    OP_MOD, /**< Modulus operator. */
    OP_LT,  /**< Less than operator. */
    OP_GT,  /**< Greater than operator. */
    OP_GE,  /**< Greater than or equal operator. */
    OP_LE,  /**< Less than or equal operator. */
    OP_NE,  /**< Not equal operator. */
    OP_EQ,  /**< Equal operator. */
    OP_AND, /**< Logical AND operator. */
    OP_OR,  /**< Logical OR operator. */
    OP_NEG  /**< Logical NOT operator. */
} OperationType;

typedef struct Node Node;
typedef struct Statement Statement;

/**
 * @struct Node
 * @brief Represents an AST node.
 *
 * Depending on the node type, different union fields are used.
 */
struct Node
{
    NodeType type; /**< Type of the node. */
    union
    {
        struct
        {
            OperationType op; /**< Operation type for an expression. */
            Node *left;       /**< Left operand. */
            Node *right;      /**< Right operand. */
        } expr;
        struct
        {
            int num; /**< Numeric value. */
        } num;
        struct
        {
            bool is_true; /**< Boolean value. */
        } boolean;
        struct
        {
            char *var_name; /**< Variable name. */
        } var;
        struct
        {
            char *var_name; /**< Array name. */
            Node *index;    /**< Index expression. */
        } arr;
        struct
        {
            ValueType type; /**< Declaration type (variable or array). */
            union
            {
                struct
                {
                    char *var_name; /**< Variable name for a declaration. */
                } var;
                struct
                {
                    char *var_name; /**< Array name for a declaration. */
                    int size;       /**< Size of the array. */
                } arr;
            } decl_var;
            Node *next; /**< Pointer to the next declaration node (for merged declarations). */
        } decl;
    } data;
};

/**
 * @struct Statement
 * @brief Represents a statement in the AST.
 *
 * A statement can be a control structure, assignment, declaration, etc.
 */
struct Statement
{
    StatementType type; /**< The type of statement. */
    union
    {
        struct
        {
            Node *cond;            /**< Condition expression for if statements. */
            Statement *then_stmts; /**< Statements to execute if condition is true. */
            Statement *else_stmts; /**< Statements to execute if condition is false. */
        } if_stmt;
        struct
        {
            Statement *init_stmt;   /**< Initialization statement for for loops. */
            Node *cond_stmt;        /**< Loop condition expression. */
            Statement *update_stmt; /**< Update statement for for loops. */
            Statement *stmts;       /**< Loop body statements. */
        } for_stmt;
        struct
        {
            Node *var_expr; /**< Variable (or array) being assigned. */
            Node *expr;     /**< Expression being assigned. */
        } assign_stmt;
        struct
        {
            bool is_string; /**< Flag indicating if the write is for a string literal. */
            union
            {
                char *string; /**< String literal to write. */
                Node *expr;   /**< Expression to write. */
            } write_data;
        } write_stmt;
        struct
        {
            SymbolType type; /**< Type of declaration (should match SymbolType). */
            Node *decls;     /**< Merged linked list of declaration nodes. */
        } decl_stmt;
    } stmt_data;
    Statement *next; /**< Pointer to the next statement (used for linking statements together). */
};

extern bool break_occured;      /**< Global flag indicating if a break statement has occurred. */
extern Statement *global_stmts; /**< Global pointer to the head of the AST for the program. */

/* ------------------------------------------------------------------------- */
/*                           Function Prototypes                             */
/* ------------------------------------------------------------------------- */

/* AST Node Creation Functions */

/**
 * @brief Creates an expression node.
 * @param op_type The operation type.
 * @param left Pointer to the left operand.
 * @param right Pointer to the right operand.
 * @return Pointer to the newly created node.
 */
Node *create_expr_node(OperationType op_type, Node *left, Node *right);

/**
 * @brief Creates a numeric constant node.
 * @param value The numeric value.
 * @return Pointer to the newly created node.
 */
Node *create_num_node(int value);

/**
 * @brief Creates a variable node.
 * @param var_name The name of the variable.
 * @return Pointer to the newly created node.
 */
Node *create_var_node(char *var_name);

/**
 * @brief Creates an array access node.
 * @param var_name The name of the array.
 * @param index Pointer to the index expression node.
 * @return Pointer to the newly created node.
 */
Node *create_array_node(char *var_name, Node *index);

/**
 * @brief Creates a boolean constant node.
 * @param is_true The boolean value.
 * @return Pointer to the newly created node.
 */
Node *create_bool_node(bool is_true);

/**
 * @brief Creates a declaration node for a variable.
 * @param var_name The name of the variable.
 * @return Pointer to the newly created declaration node.
 */
Node *create_var_decl_node(char *var_name);

/**
 * @brief Creates a declaration node for an array.
 * @param var_name The name of the array.
 * @param size The size of the array.
 * @return Pointer to the newly created declaration node.
 */
Node *create_arr_decl_node(char *var_name, int size);

/* AST Statement Creation Functions */

/**
 * @brief Creates an assignment statement.
 * @param var_expr The left-hand side variable (or array) node.
 * @param expr The right-hand side expression node.
 * @return Pointer to the newly created statement.
 */
Statement *create_assign_stmt(Node *var_expr, Node *expr);

/**
 * @brief Creates a for loop statement.
 * @param init Pointer to the initialization statement.
 * @param cond Pointer to the condition expression.
 * @param update Pointer to the update statement.
 * @param stmts Pointer to the loop body statements.
 * @return Pointer to the newly created for loop statement.
 */
Statement *create_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts);

/**
 * @brief Creates an if statement.
 * @param cond Pointer to the condition expression.
 * @param then_stmts Pointer to the then branch statements.
 * @param else_stmts Pointer to the else branch statements.
 * @return Pointer to the newly created if statement.
 */
Statement *create_if_stmt(Node *cond, Statement *then_stmts, Statement *else_stmts);

/**
 * @brief Creates a write statement.
 * @param is_str True if writing a string literal; false if writing an expression.
 * @param expr Pointer to the expression node (if not a string).
 * @param string The string literal (if is_str is true).
 * @return Pointer to the newly created write statement.
 */
Statement *create_write_stmt(bool is_str, Node *expr, char *string);

/**
 * @brief Creates a break statement.
 * @return Pointer to the newly created break statement.
 */
Statement *create_break_stmt();

/**
 * @brief Creates a declaration statement.
 * @param type The symbol type for the declarations.
 * @param decls Pointer to the merged declaration nodes.
 * @return Pointer to the newly created declaration statement.
 */
Statement *create_decl_stmt(SymbolType type, Node *decls);

/**
 * @brief Merges the three AST segments into one contiguous chain.
 *
 * The segments merged are:
 * - Global declarations (gdecls)
 * - Local declarations (ldecls)
 * - Main block statements (mainblock)
 *
 * @param gdecls Pointer to the head of global declaration statements.
 * @param ldecls Pointer to the head of local declaration statements.
 * @param mainblock Pointer to the head of main block statements.
 * @return Pointer to the head of the merged AST.
 */
Statement *merge_ast_segments(Statement *gdecls, Statement *ldecls, Statement *mainblock);

/* Evaluation Functions */

/**
 * @brief Evaluates the entire AST of statements.
 * @param stmts Pointer to the head of the statement list.
 */
void eval_stmts(Statement *stmts);

/**
 * @brief Evaluates an assignment statement.
 * @param var_expr The left-hand side variable (or array) node.
 * @param expr The right-hand side expression node.
 */
void eval_assign_stmt(Node *var_expr, Node *expr);

/**
 * @brief Evaluates an if statement.
 * @param cond Pointer to the condition expression.
 * @param then_stmts Pointer to the then branch statements.
 * @param else_stmts Pointer to the else branch statements.
 */
void eval_if_stmt(Node *cond, Statement *then_stmts, Statement *else_stmts);

/**
 * @brief Evaluates a for loop statement.
 * @param init Pointer to the initialization statement.
 * @param cond Pointer to the condition expression.
 * @param update Pointer to the update statement.
 * @param stmts Pointer to the loop body statements.
 */
void eval_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts);

/**
 * @brief Checks if the given yields a boolean node or not.
 * @param expr Node that is to be checked.
 * @return true if the node yields a boolean value false else.
 */
bool is_boolean_expr(Node *expr);

/**
 * @brief Evaluates a write statement.
 * @param is_str True if writing a string literal; false if writing an expression.
 * @param expr Pointer to the expression node (if not a string).
 * @param string The string literal (if is_str is true).
 */
void eval_write_stmt(bool is_str, Node *expr, char *string);

/**
 * @brief Evaluates a break statement.
 */
void eval_break_stmt();

/**
 * @brief Evaluates a declaration statement.
 * @param type The symbol type for the declarations.
 * @param decls Pointer to the merged declaration nodes.
 */
void eval_decl_stmt(SymbolType type, Node *decls);

/**
 * @brief Evaluates an expression node and returns an integer value.
 * @param expr Pointer to the expression node.
 * @return The evaluated integer value.
 */
int eval_expr_int(Node *expr);

/**
 * @brief Evaluates an expression node and returns a boolean value.
 * @param expr Pointer to the expression node.
 * @return The evaluated boolean value.
 */
bool eval_expr_bool(Node *expr);

/* Memory Freeing Functions */

/**
 * @brief Frees the entire AST of statements.
 */
void free_statements();

/**
 * @brief Frees a chain of declaration nodes.
 * @param decl Pointer to the first declaration node.
 */
void free_decl(Node *decl);

/**
 * @brief Frees an expression node and its subnodes.
 * @param expr Pointer to the expression node.
 */
void free_expr(Node *expr);

/**
 * @brief Recursively frees a statement node and its sub-statements.
 * @param stmt Pointer to the statement node.
 */
void free_statement_rec(Statement *stmt);

/* AST Printing Functions */

/**
 * @brief Prints the branch prefix for the AST tree.
 * @param prefix The accumulated prefix string.
 * @param isLast True if this branch is the last child.
 */
void print_tree_prefix(const char *prefix, bool isLast);

/**
 * @brief Recursively prints an expression node in a tree-like format.
 * @param expr Pointer to the expression node.
 * @param prefix The prefix string for formatting.
 * @param isLast True if this node is the last child.
 */
void print_ast_expr(Node *expr, const char *prefix, bool isLast);

/**
 * @brief Recursively prints a statement node in a tree-like format.
 * @param stmt Pointer to the statement node.
 * @param prefix The prefix string for formatting.
 * @param isLast True if this statement is the last child.
 */
void print_ast_stmt(Statement *stmt, const char *prefix, bool isLast);

/**
 * @brief Prints a list of statement nodes in a tree-like format.
 * @param stmts Pointer to the head of the statement list.
 * @param prefix The prefix string for formatting.
 */
void print_ast_stmt_list(Statement *stmts, const char *prefix);

/**
 * @brief Prints the entire AST.
 */
void print_ast(void);

#endif
