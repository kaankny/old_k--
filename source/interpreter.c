#include "../include/interpreter.h"
#include <stdlib.h>
#include "../include/memory.h"
#include "../include/utils.h"
#include <stdio.h>
#include "../include/AST.h"
#include "../include/scope.h"
#include <string.h>

ASTNode *interpreter_visit_variable(Interpreter *interpreter, ASTNode *node)
{
	ASTNode *variable_definition = scope_get_variable_definition(node->scope, node->variable_name);
	if (variable_definition)
		return (interpreter_visit(interpreter, variable_definition->variable_defination_value));
	start_print_error();
	printf("Variable not found: %s\n", node->variable_name);
	end_print_error();
	free_memory();
	exit(1);
	return (NULL);
}

static ASTNode *builtim_function_input(Interpreter *interpreter, ASTNode *node)
{
	char *input = (char *)calloc(sizeof(char), 1024);
	scanf("%s", input);
	for(int i = 0; i < node->scope->variable_definitions_count; i++)
	{
		ASTNode *variable_definition = node->scope->variable_definitions[i];
		if (strcmp(variable_definition->variable_defination_variable_name, node->function_call_arguments[0]->variable_name) == 0)
		{
			variable_definition->variable_defination_value = ast_init(AST_STRING);
			variable_definition->variable_defination_value->string = input;
			return (ast_init(AST_NOOP));
		}
	}
	start_print_error();
	printf("Variable not found!: %s\n", node->function_call_arguments[0]->variable_name);
	end_print_error();
	free_memory();
	exit(1);
}

static ASTNode *builtin_function_print(Interpreter *interpreter, ASTNode *node)
{
	for(int i = 0; i < node->function_call_arguments_count; i++)
	{
		ASTNode *argument = node->function_call_arguments[i];
		if (argument->type == AST_STRING)
			printf("%s", argument->string);
		else if (argument->type == AST_VARIABLE)
		{
			ASTNode *value = interpreter_visit_variable(interpreter, argument);
			if (value->type == AST_STRING)
				printf("%s ", value->string);
			else if (value->type == AST_NUMBER)
				printf("%d ", value->number);
			else
			{
				start_print_error();
				printf("Invalid argument type for print function %s\n", value->variable_name);
				end_print_error();
				free_memory();
				exit(1);
			}
		}
		else if (argument->type == AST_NUMBER)
			printf("%d", argument->number);
		else if (argument->type == AST_FLOAT)
			printf("%f", argument->float_number);
		else
		{
			start_print_error();
			printf("Invalid argument type for print function %s %d\n", argument->string, argument->type);
			end_print_error();
			free_memory();
			exit(1);
		}
	}
	return (ast_init(AST_NOOP));
}

Interpreter	*interpreter_init(void)
{
	Interpreter *interpreter = (Interpreter *)calloc(sizeof(Interpreter), 1);
	interpreter->variable_definitions = NULL;
	interpreter->variable_definitions_count = 0;
	return (interpreter);
}

ASTNode *interpreter_visit_variable_defination(Interpreter *interpreter, ASTNode *node)
{
	scope_add_variable_definition(node->scope, node);
	return (node);
}


ASTNode *interpreter_visit_function_call(Interpreter *interpreter, ASTNode *node)
{
	if (strcmp(node->function_call_name, "print") == 0)
		return (builtin_function_print(interpreter, node));
	if (strcmp(node->function_call_name, "println") == 0)
	{
		builtin_function_print(interpreter, node);
		printf("\n");
		return (ast_init(AST_NOOP));
	}
	else if (strcmp(node->function_call_name, "input") == 0)
		return (builtim_function_input(interpreter, node));
	
	ASTNode *function_definition = scope_get_function_definition(node->scope, node->function_call_name);
	if (!function_definition)
	{
		start_print_error();
		printf("Function not found: %s\n", node->function_call_name);
		end_print_error();
		free_memory();
		exit(1);
	}
	for(int i = 0; i < function_definition->function_definition_arguments_count; i++)
	{
		ASTNode *argument = function_definition->function_definition_arguments[i];
		ASTNode *value = interpreter_visit(interpreter, node->function_call_arguments[i]);
		ASTNode *variable_definition = ast_init(AST_VARIABLE_DEFINITION);
		variable_definition->variable_defination_variable_name = argument->variable_name;
		variable_definition->variable_defination_value = value;
		variable_definition->variable_defination_variable_type = argument->type;
		variable_definition->scope = function_definition->scope;
		interpreter_visit_variable_defination(interpreter, variable_definition);
	}
	return (interpreter_visit(interpreter, function_definition->function_definition_body));
}

ASTNode *interpreter_visit_string(Interpreter *interpreter, ASTNode *node)
{
	return (node);
}

ASTNode *interpreter_visit_compound(Interpreter *interpreter, ASTNode *node)
{
	for (int i = 0; i < node->compound_value_count; i++)
		interpreter_visit(interpreter, node->compound_value[i]);
	return (ast_init(AST_NOOP));
}

ASTNode *interpreter_function_defination(Interpreter *interpreter, ASTNode *node)
{
	scope_add_function_definition(node->scope, node);
	return (node);
}

ASTNode *interpreter_visit_variable_assignment(Interpreter *interpreter, ASTNode *node)
{
	ASTNode *variable_definition = scope_get_variable_definition(node->scope, node->variable_assignment_variable_name);
	if (variable_definition)
	{
		if (variable_definition->variable_defination_variable_type != node->variable_assignment_variable_type)
		{
			start_print_error();
			printf("Variable type mismatch: %s\n", node->variable_assignment_variable_name);
			end_print_error();
			free_memory();
			exit(1);
		}
		ASTNode *value = interpreter_visit(interpreter, node->variable_assignment_value);
		variable_definition->variable_defination_value = value;
		return (ast_init(AST_NOOP));
	}
	start_print_error();
	printf("Variable not found: %s\n", node->variable_assignment_variable_name);
	end_print_error();
	free_memory();
	exit(1);
	return (NULL);
}

ASTNode *interpreter_visit(Interpreter *interpreter, ASTNode *node)
{
	ASTNodeType	type = node->type;

	if (type == AST_VARIABLE_DEFINITION)
		return (interpreter_visit_variable_defination(interpreter, node));
	else if (type == AST_VARIABLE)
		return (interpreter_visit_variable(interpreter, node));
	else if (type == AST_FUNCTION_CALL)
		return (interpreter_visit_function_call(interpreter, node));
	else if (type == AST_FUNCTION_DEFINITION)
		return (interpreter_function_defination(interpreter, node));
	else if (type == AST_VARIABLE_ASSIGNMENT)
		return (interpreter_visit_variable_assignment(interpreter, node));
	else if (type == AST_STRING)
		return (interpreter_visit_string(interpreter, node));
	else if (type == AST_FLOAT)
		return (node);
	else if (type == AST_COMPOUND)
		return (interpreter_visit_compound(interpreter, node));
	else if (type == AST_NUMBER)
	{
		return (node);
	}
	else if (type == AST_NOOP)
		return (ast_init(AST_NOOP));
	else
	{
		start_print_error();
		printf("Unexpected AST node type: %d\n", type);
		end_print_error();
		free_memory();
		exit(1);
	}
	return (NULL);
}