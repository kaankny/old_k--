#include "../include/AST.h"
#include <stdlib.h>
#include "../include/memory.h"

ASTNode	*ast_init(ASTNodeType type)
{
	ASTNode *node = (ASTNode *)calloc(sizeof(ASTNode), 1);
	node->type = type;

	node->scope = NULL;

	node->variable_defination_variable_name = NULL;
	node->variable_defination_variable_type = 0;
	node->variable_defination_value = NULL;
	node->variable_name = NULL;

	node->function_definition_body = NULL;
	node->function_definition_name = NULL;
	node->function_definition_arguments = NULL;
	node->function_definition_arguments_count = 0;

	node->function_call_name = NULL;
	node->function_call_arguments = NULL;
	node->function_call_arguments_count = 0;

	node->string = NULL;
	node->number = 0;

	node->variable_assignment_variable_name = NULL;
	node->variable_assignment_value = NULL;

	node->compound_value = NULL;
	node->compound_value_count = 0;
	return (node);
}
