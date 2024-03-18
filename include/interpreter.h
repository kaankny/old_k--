#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "AST.h"

typedef struct
{
	ASTNode			**variable_definitions;
	unsigned int	variable_definitions_count;
}	Interpreter;

Interpreter	*interpreter_init();
ASTNode		*interpreter_visit(Interpreter *interpreter, ASTNode *node);

#endif