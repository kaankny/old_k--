#ifndef AST_H
#define AST_H

#include "./lexer.h"

/*
**	Abstract Syntax Tree Node Types
*/
typedef enum ASTNodeType
{
	AST_NOOP,
	AST_VARIABLE_DEFINITION,
	AST_VARIABLE,
	AST_FUNCTION_DEFINITION,
	AST_FUNCTION_CALL,
	AST_VARIABLE_ASSIGNMENT,
	AST_EQUAL,
	AST_IF,
	AST_STRING,
	AST_NUMBER,
	AST_FLOAT,
	AST_BOOLEAN,
	AST_COMPOUND
}	ASTNodeType;

typedef struct ASTNode
{
	ASTNodeType 	type;

	struct Scope	*scope;


	char			*variable_defination_variable_name;
	struct ASTNode	*variable_defination_value;
	TokenType		variable_defination_variable_type;
	char			*variable_name;

	struct ASTNode	*function_definition_body;
	char			*function_definition_name;
	struct ASTNode	**function_definition_arguments;
	unsigned int	function_definition_arguments_count;

	char			*function_call_name;
	struct ASTNode	**function_call_arguments;
	unsigned int	function_call_arguments_count;

	char			*variable_assignment_variable_name;
	struct ASTNode	*variable_assignment_value;
	TokenType		variable_assignment_variable_type;

	char			*string;	
	int				number;
	float 			float_number;

	struct ASTNode	**compound_value;
	unsigned int	compound_value_count;

	int				boolean;

	struct ASTNode	*equal_left;
	struct ASTNode	*equal_right;

	struct ASTNode	*if_condition;
	struct ASTNode	*else_body;
	struct ASTNode	*if_body;
}	ASTNode;

ASTNode	*ast_init(ASTNodeType type);

#endif