#include "../include/AST.h"
#include <stdlib.h>
#include "../include/memory.h"
#include "../include/utils.h"
#include <stdio.h>
#include "../include/scope.h"
#include <string.h>

Scope	*scope_init()
{
	Scope *scope = (Scope *)calloc(sizeof(Scope), 1);
	scope->function_definitions = NULL;
	scope->function_definitions_count = 0;
	scope->variable_definitions = NULL;
	scope->variable_definitions_count = 0;
	return (scope);
}

ASTNode	*scope_add_function_definition(Scope *scope, ASTNode *function_definition)
{
	scope->function_definitions = (ASTNode **)realloc(scope->function_definitions, sizeof(ASTNode *) * (scope->function_definitions_count + 1));
	scope->function_definitions[scope->function_definitions_count] = function_definition;
	scope->function_definitions_count++;
	return (function_definition);
}

ASTNode	*scope_get_function_definition(Scope *scope, char *name)
{
	for (int i = 0; i < scope->function_definitions_count; i++)
	{
		if (strcmp(scope->function_definitions[i]->function_definition_name, name) == 0)
			return (scope->function_definitions[i]);
	}
	return (NULL);
}

ASTNode	*scope_add_variable_definition(Scope *scope, ASTNode *variable_definition)
{
	scope->variable_definitions = (ASTNode **)realloc(scope->variable_definitions, sizeof(ASTNode *) * (scope->variable_definitions_count + 1));
	scope->variable_definitions[scope->variable_definitions_count] = variable_definition;
	scope->variable_definitions_count++;
	return (variable_definition);
}

ASTNode	*scope_get_variable_definition(Scope *scope, char *name)
{
	for (int i = 0; i < scope->variable_definitions_count; i++)
	{
		if (strcmp(scope->variable_definitions[i]->variable_defination_variable_name, name) == 0)
			return (scope->variable_definitions[i]);
	}
	return (NULL);
}
