#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100

/**
 * @brief Global flag for break statement.
 */
extern bool breakFlag;

/**
 * @brief Enumeration for symbol types.
 */
typedef enum
{
    SYMBOL_INT,       /**< Integer symbol type */
    SYMBOL_INT_ARRAY, /**< Integer array symbol type */
    SYMBOL_BOOL
} SymbolType;

/**
 * @brief Union representing a symbol's value.
 */
typedef union
{
    struct
    {
        int value;       /**< Integer value */
        bool is_defined; /**< Flag indicating if the integer is defined */
    } int_value;
    struct
    {
        int *array; /**< Pointer to integer array */
        int size;   /**< Size of the array */
    } int_array;
} SymbolValue;

/**
 * @brief Structure representing a symbol in the symbol table.
 */
typedef struct Symbol
{
    char *name;          /**< Name of the symbol */
    SymbolType type;     /**< Type of the symbol */
    SymbolValue value;   /**< Value of the symbol */
    struct Symbol *next; /**< Pointer to the next symbol in the table */
} Symbol;

/**
 * @brief The symbol table as an array of symbol pointers.
 */
extern Symbol *symbol_table[TABLE_SIZE];

/**
 * @brief Initializes the symbol table.
 */
void init_symbol_table();

/**
 * @brief Computes the hash value for a given key.
 *
 * @param key The key to hash.
 * @return The computed hash value.
 */
unsigned int hash(const char *key);

/**
 * @brief Creates an integer symbol with the given key, value, and defined status.
 *
 * @param key The symbol name.
 * @param value The integer value.
 * @param is_defined Boolean indicating if the symbol is defined.
 */
void create_symbol_int(const char *key, int value, bool is_defined);

/**
 * @brief Updates the integer symbol with a new value.
 *
 * @param key The symbol name.
 * @param new_value The new integer value.
 */
void update_symbol_int(const char *key, int new_value);

/**
 * @brief Creates an integer array symbol with the specified key and size.
 *
 * @param key The symbol name.
 * @param size The size of the array.
 */
void create_symbol_array(const char *key, int size);

/**
 * @brief Updates an element of an integer array symbol.
 *
 * @param key The symbol name.
 * @param index The index of the element to update.
 * @param value The new value for the element.
 */
void update_symbol_array(const char *key, int index, int value);

/**
 * @brief Searches for a symbol in the symbol table.
 *
 * @param key The symbol name to search for.
 * @return Pointer to the found symbol, or NULL if not found.
 */
Symbol *search_symbol(const char *key);

/**
 * @brief Frees the memory allocated for a symbol.
 *
 * @param symbol The symbol to free.
 */
void free_symbol(Symbol *symbol);

/**
 * @brief Frees the entire symbol table.
 */
void free_symbol_table();

/**
 * @brief Prints the symbol table.
 */
void print_symbol_table();

/**
 * @brief Prints a newline character.
 */
static inline void endl() { printf("\n"); }

/**
 * @brief Enumeration for variable types.
 */
typedef enum
{
    VARIABLE, /**< Single variable type */
    ARRAY  /**< Array variable type */
} VarType;

/**
 * @brief Structure representing variable data for declarations.
 */
typedef struct VariableData
{
    VarType type; /**< Type of the variable (VAR or ARR) */
    union
    {
        struct
        {
            char *name; /**< Variable name */
        } single;
        struct
        {
            char *name; /**< Array name */
            int size;   /**< Array size */
        } array;
    } data;
    struct VariableData *next; /**< Pointer to the next variable data */
} VariableData;

/**
 * @brief Node structure for variable declarations.
 */
typedef struct DeclNode
{
    SymbolType type;       /**< Type of the symbol */
    char *type_name;       /**< Name of the type */
    VariableData **var;    /**< Array of pointers to variable data */
    int var_count;         /**< Number of variables */
    struct DeclNode *next; /**< Pointer to the next declaration node */
} DeclNode;

/**
 * @brief Enumeration for declaration scope types.
 */
typedef enum
{
    SCOPE_GLOBAL, /**< Global scope */
    SCOPE_LOCAL,  /**< Local scope */
    SCOPE_LOOP    /**< Loop scope */
} DeclScopeType;

/**
 * @brief Structure representing a declaration scope.
 */
typedef struct DeclScope
{
    DeclScopeType scope; /**< The scope type */
    DeclNode *decl_list; /**< Linked list of declaration nodes */
} DeclScope;

/**
 * @brief Global declarations.
 */
extern DeclScope *global_decls;

/**
 * @brief Initializes global declarations.
 */
void initialize_global();

/**
 * @brief Adds a global variable declaration.
 *
 * @param key The variable name.
 * @return Pointer to the created variable data.
 */
VariableData *add_var(char *key);

/**
 * @brief Adds a global array declaration.
 *
 * @param key The array name.
 * @param size The size of the array.
 * @return Pointer to the created variable data.
 */
VariableData *add_arr(char *key, int size);

/**
 * @brief Adds all the symbols in the variable list to the global declaration.
 *
 * @param type The symbol type.
 * @param var_list The head of the linked list containing variable declarations.
 */
void add_symbols(SymbolType type, VariableData *var_list);

/**
 * @brief Prints all global declarations.
 */
void print_decls();

/**
 * @brief Frees all global declarations.
 */
void free_decls();

/**
 * @brief Enumeration for statement types.
 */
typedef enum
{
    STMT_ASSIGN, /**< Assignment statement */
    STMT_WRITE,  /**< Write statement */
    STMT_IF,     /**< If statement */
    STMT_FOR,    /**< For loop statement */
    STMT_BREAK   /**< Break statement */
} StatementType;

/**
 * @brief Enumeration for AST node types.
 */
typedef enum
{
    NODE_NUM,    /**< Numeric literal node */
    NODE_VAR,    /**< Variable node */
    NODE_ARRAY,  /**< Array access node */
    NODE_EXPR,   /**< Expression node */
    NODE_ASSIGN, /**< Assignment node */
    NODE_WRITE,  /**< Write statement node */
    NODE_IF,     /**< If statement node */
    NODE_FOR,    /**< For loop node */
    NODE_BOOL,   /**< Boolean literal node */
    NODE_STRING, /**< String literal node */
    NODE_BREAK   /**< Break statement node */
} NodeType;

/**
 * @brief Enumeration for operation types in expressions.
 */
typedef enum
{
    TOKEN_ADD, /**< Addition */
    TOKEN_SUB, /**< Subtraction */
    TOKEN_MUL, /**< Multiplication */
    TOKEN_DIV, /**< Division */
    TOKEN_MOD, /**< Modulus */
    TOKEN_LT,  /**< Less than */
    TOKEN_GT,  /**< Greater than */
    TOKEN_GE,  /**< Greater than or equal */
    TOKEN_LE,  /**< Less than or equal */
    TOKEN_NE,  /**< Not equal */
    TOKEN_EQ,  /**< Equal */
    TOKEN_NOT, /**< Logical NOT */
    TOKEN_AND, /**< Logical AND */
    TOKEN_OR   /**< Logical OR */
} OperationType;

/**
 * @brief Structure representing an AST node.
 */
typedef struct Node
{
    NodeType nodetype; /**< Type of the node */
    union
    {
        struct
        {
            struct Node *var_expr; /**< Variable expression for assignment */
            struct Node *expr;     /**< Expression to assign */
        } assign;
        struct
        {
            struct Node *expr; /**< Expression for write statement */
        } write;
        struct
        {
            struct Node *cond;           /**< Condition for if statement */
            struct Statement *then_stmt; /**< Statement executed if condition is true */
            struct Statement *else_stmt; /**< Statement executed if condition is false */
        } if_stmt;
        struct
        {
            struct Statement *init;   /**< Initialization statement for loop */
            struct Node *cond;        /**< Loop condition */
            struct Statement *update; /**< Update statement for loop */
            struct Statement *stmts;  /**< Loop body statements */
        } for_stmt;
        struct
        {
            OperationType op;   /**< Operation type */
            struct Node *left;  /**< Left operand */
            struct Node *right; /**< Right operand */
        } expr;
        struct
        {
            int val; /**< Numeric value */
        } num;
        struct
        {
            char *var; /**< Variable name */
        } var;
        struct
        {
            char *var;        /**< Array name */
            struct Node *idx; /**< Index node for array access */
        } array;
        struct
        {
            bool boolean; /**< Boolean value */
        } boolean;
        struct
        {
            char *str; /**< String literal */
        } string;
    } data;
} Node;

/**
 * @brief Structure representing a statement.
 */
typedef struct Statement
{
    StatementType stmt_type; /**< Type of the statement */
    Node *stmt;              /**< Associated AST node */
    struct Statement *next;  /**< Pointer to the next statement */
} Statement;

/**
 * @brief Creates a generic statement.
 *
 * @param stmt_type The type of the statement.
 * @param stmt The associated AST node.
 * @param next The next statement in the sequence.
 * @return Pointer to the created statement.
 */
Statement *create_statement(StatementType stmt_type, Node *stmt, Statement *next);

/**
 * @brief Creates an assignment statement.
 *
 * @param var_expr The variable expression node.
 * @param expr The expression node to assign.
 * @return Pointer to the created assignment statement.
 */
Statement *create_assign_stmt(Node *var_expr, Node *expr);

/**
 * @brief Creates a for loop statement.
 *
 * @param init The initialization statement.
 * @param cond The loop condition node.
 * @param update The update statement.
 * @param stmts The body statements.
 * @return Pointer to the created for loop statement.
 */
Statement *create_for_stmt(Statement *init, Node *cond, Statement *update, Statement *stmts);

/**
 * @brief Creates an if statement.
 *
 * @param cond The condition node.
 * @param if_stmt The statement executed if condition is true.
 * @param else_stmt The statement executed if condition is false.
 * @return Pointer to the created if statement.
 */
Statement *create_if_stmt(Node *cond, Statement *if_stmt, Statement *else_stmt);

/**
 * @brief Creates a write statement for an expression.
 *
 * @param expr The expression node to write.
 * @return Pointer to the created write statement.
 */
Statement *create_write_stmt(Node *expr);

/**
 * @brief Creates a write statement for a string literal.
 *
 * @param str The string literal.
 * @return Pointer to the created write statement.
 */
Statement *create_write_stmt_string(char *str);

/**
 * @brief Creates a break statement.
 *
 * @return Pointer to the created break statement.
 */
Statement *create_break_stmt(void);

/**
 * @brief Creates an AST node for a variable.
 *
 * @param var The variable name.
 * @return Pointer to the created variable node.
 */
Node *create_var_node(char *var);

/**
 * @brief Creates an AST node for an array access.
 *
 * @param var The array name.
 * @param idx_node The index node.
 * @return Pointer to the created array access node.
 */
Node *create_array_node(char *var, Node *idx_node);

/**
 * @brief Creates an AST node for an expression.
 *
 * @param op The operation type.
 * @param left The left operand node.
 * @param right The right operand node.
 * @return Pointer to the created expression node.
 */
Node *create_expr_node(OperationType op, Node *left, Node *right);

/**
 * @brief Creates an AST node for a numeric literal.
 *
 * @param value The numeric value.
 * @return Pointer to the created numeric node.
 */
Node *create_num_node(int value);

/**
 * @brief Creates an AST node for a boolean literal.
 *
 * @param boolean The boolean value.
 * @return Pointer to the created boolean node.
 */
Node *create_bool_node(bool boolean);

/**
 * @brief Evaluates a sequence of statements.
 *
 * @param stmt Pointer to the first statement.
 * @return Boolean indicating success or failure of evaluation.
 */
bool eval_stmts(Statement *stmt);

/**
 * @brief Evaluates an assignment statement.
 *
 * @param assign_stmt The assignment AST node.
 */
void eval_assign(Node *assign_stmt);

/**
 * @brief Evaluates an expression node and returns its integer value.
 *
 * @param expr The expression node.
 * @return The evaluated integer value.
 */
int eval_expr_val(Node *expr);

/**
 * @brief Evaluates an expression node and returns its boolean value.
 *
 * @param expr The expression node.
 * @return The evaluated boolean value.
 */
bool eval_expr_bool(Node *expr);

/**
 * @brief Evaluates a for loop statement.
 *
 * @param for_stmt The for loop statement.
 */
void eval_for(Node *for_stmt);

/**
 * @brief Evaluates an if statement.
 *
 * @param if_stmt The if statement node.
 */
void eval_if(Node *if_stmt);

/**
 * @brief Evaluates a write statement.
 *
 * @param write_stmt The write statement node.
 */
void eval_write(Node *write_stmt);

/**
 * @brief Evaluates a break statement.
 *
 * @param break_node The break statement node.
 */
void eval_break(Node *break_node);

/**
 * @brief Prints the given prefix string.
 *
 * @param prefix The prefix string to print.
 */
void print_prefix(const char *prefix);

/**
 * @brief Constructs the child prefix based on the parent's prefix.
 *
 * @param parentPrefix The parent's prefix string.
 * @param isLast Boolean indicating if the current node is the last child.
 * @param childPrefix Buffer to store the child prefix.
 * @param size Size of the buffer.
 */
void make_child_prefix(const char *parentPrefix, bool isLast, char *childPrefix, size_t size);

/**
 * @brief Prints an AST node with the given prefix.
 *
 * @param node The AST node to print.
 * @param prefix The prefix string.
 * @param isLast Boolean indicating if the node is the last in its group.
 */
void print_node(Node *node, const char *prefix, bool isLast);

/**
 * @brief Prints a sequence of statements with the given prefix.
 *
 * @param stmt The first statement in the sequence.
 * @param prefix The prefix string.
 */
void print_statements(Statement *stmt, const char *prefix);

/**
 * @brief Frees the memory allocated for an AST node.
 *
 * @param node The node to free.
 */
void free_node(Node *node);

/**
 * @brief Frees the memory allocated for a sequence of statements.
 *
 * @param stmt The first statement in the sequence to free.
 */
void free_statements(Statement *stmt);

#endif // COMPILER_H
