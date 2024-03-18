#ifndef SCOPE_H
#define SCOPE_H

#include "AST.h"

typedef struct Scope {
	ASTNode			**function_definitions;
	unsigned int	function_definitions_count;

	ASTNode			**variable_definitions;
	unsigned int	variable_definitions_count;
}	Scope;

Scope	*scope_init();

ASTNode	*scope_add_function_definition(Scope *scope, ASTNode *function_definition);
ASTNode	*scope_get_function_definition(Scope *scope, char *name);

ASTNode	*scope_add_variable_definition(Scope *scope, ASTNode *variable_definition);
ASTNode	*scope_get_variable_definition(Scope *scope, char *name);

#endif