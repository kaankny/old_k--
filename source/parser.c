#include "../include/AST.h"
#include "../include/parser.h"
#include <stdlib.h>
#include "../include/lexer.h"
#include <stdio.h>
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/scope.h"
#include <string.h>

Parser	*parser_init(Token *tokens)
{
	Parser *parser = (Parser *)calloc(sizeof(Parser), 1);
	parser->tokens = tokens;
	parser->current_token = tokens;
	parser->scope = scope_init();
	return (parser);
}

void	parser_advance(Parser *parser, TokenType type)
{
	if (parser->current_token->type != type)
	{
		start_print_error();
		printf("Unexpected token '%s', expected '%d'\n", parser->current_token->string_content, type);
		end_print_error();
		free_memory();
		exit(1);
	}
	parser->current_token = parser->current_token->next;
}

ASTNode *parser_parse_variable_assignment(Parser *parser, Scope *scope)
{
	ASTNode *ast_variable_assignment = ast_init(AST_VARIABLE_ASSIGNMENT);
	ast_variable_assignment->variable_assignment_variable_name = parser->current_token->string_content;
	parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	parser_advance(parser, TOKEN_TYPE_ASSIGN);
	TokenType type = parser->current_token->type;
	ast_variable_assignment->variable_assignment_value = parser_parse_expression(parser, parser->current_token->type, scope);
	ast_variable_assignment->variable_assignment_variable_type = type;
	ast_variable_assignment->scope = scope;
	return (ast_variable_assignment);
}

ASTNode	*parser_parse_equal(Parser *parser, Scope *scope)
{
	ASTNode *ast_equal = ast_init(AST_EQUAL);
	if (parser->current_token->type == TOKEN_TYPE_IDENTIFIER)
	{
		ast_equal->equal_left = ast_init(AST_VARIABLE);
		ast_equal->equal_left->variable_name = parser->current_token->string_content;
		parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	}
	else if (parser->current_token->type == TOKEN_TYPE_STRING)
	{
		ast_equal->equal_left = ast_init(AST_STRING);
		ast_equal->equal_left->string = parser->current_token->string_content;
		parser_advance(parser, TOKEN_TYPE_STRING);
	}
	else if (parser->current_token->type == TOKEN_TYPE_NUMBER)
	{
		ast_equal->equal_left = ast_init(AST_NUMBER);
		ast_equal->equal_left->number = parser->current_token->int_content;
		parser_advance(parser, TOKEN_TYPE_NUMBER);
	}
	else if (parser->current_token->type == TOKEN_TYPE_FLOAT)
	{
		ast_equal->equal_left = ast_init(AST_FLOAT);
		ast_equal->equal_left->float_number = parser->current_token->float_content;
		parser_advance(parser, TOKEN_TYPE_FLOAT);
	}
	else if (parser->current_token->type == TOKEN_TYPE_BOOL)
	{
		ast_equal->equal_left = ast_init(AST_BOOLEAN);
		ast_equal->equal_left->boolean = parser->current_token->int_content;
		parser_advance(parser, TOKEN_TYPE_BOOL);
	}
	parser_advance(parser, TOKEN_TYPE_EQUAL);
	ast_equal->equal_right = parser_parse_expression(parser, parser->current_token->type, scope);
	ast_equal->scope = scope;
	return (ast_equal);
}

ASTNode	*parser_parse_variable(Parser *parser, TokenType type, Scope *scope)
{
	if (parser->current_token->next->type == TOKEN_TYPE_COLON)
		return (parser_parse_funcation_call(parser, scope));
	else if (parser->current_token->next->type == TOKEN_TYPE_ASSIGN)
		return (parser_parse_variable_assignment(parser, scope));
	else if (parser->current_token->next->type == TOKEN_TYPE_EQUAL)
		return (parser_parse_equal(parser, scope));
	ASTNode *ast_variable = ast_init(AST_VARIABLE);
	ast_variable->variable_name = parser->current_token->string_content;
	if (parser->current_token->type == TOKEN_TYPE_IDENTIFIER)
		parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	else
		parser_advance(parser, type);
	ast_variable->variable_defination_variable_type = type;
	ast_variable->scope = scope;
	return (ast_variable);
}

ASTNode	*parser_parse_string(Parser *parser, Scope *scope)
{
	ASTNode *ast_string = ast_init(AST_STRING);
	ast_string->string = parser->current_token->string_content;
	parser_advance(parser, TOKEN_TYPE_STRING);
	ast_string->scope = scope;
	return (ast_string);
}

ASTNode	*parser_parse_number(Parser *parser, Scope *scope)
{
	if (parser->current_token->next->type == TOKEN_TYPE_EQUAL)
		return (parser_parse_equal(parser, scope));
	ASTNode *ast_number = ast_init(AST_NUMBER);
	ast_number->number = parser->current_token->int_content;
	parser_advance(parser, TOKEN_TYPE_NUMBER);
	ast_number->scope = scope;
	return (ast_number);
}

ASTNode	*parser_parse_float(Parser *parser, Scope *scope)
{
	ASTNode *ast_float = ast_init(AST_FLOAT);
	ast_float->float_number = parser->current_token->float_content;
	parser_advance(parser, TOKEN_TYPE_NUMBER);
	ast_float->scope = scope;
	return (ast_float);
}

ASTNode	*parser_parse_boolean(Parser *parser, Scope *scope)
{
	ASTNode *ast_boolean = ast_init(AST_BOOLEAN);
	ast_boolean->boolean = parser->current_token->int_content;
	parser_advance(parser, TOKEN_TYPE_BOOL);
	ast_boolean->scope = scope;
	return (ast_boolean);
}

ASTNode	*parser_parse_expression(Parser *parser, TokenType type, Scope *scope)
{
	if (type == TOKEN_TYPE_IDENTIFIER)
		return (parser_parse_variable(parser, type, scope));
	else if (type == TOKEN_TYPE_STRING)
		return (parser_parse_string(parser, scope));
	else if (type == TOKEN_TYPE_NUMBER)
		return (parser_parse_number(parser, scope));
	else if (type == TOKEN_TYPE_FLOAT)
		return (parser_parse_float(parser, scope));
	else if (type == TOKEN_TYPE_BOOL)
		return (parser_parse_boolean(parser, scope));
	return (ast_init(AST_NOOP));
}

ASTNode	*parser_parse_funcation_call(Parser *parser, Scope *scope)
{
	ASTNode *ast_function_call = ast_init(AST_FUNCTION_CALL);
	ast_function_call->function_call_name = parser->current_token->string_content;
	parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	parser_advance(parser, TOKEN_TYPE_COLON);
	ast_function_call->function_call_arguments = (ASTNode **)calloc(sizeof(ASTNode *), 1);
	ast_function_call->function_call_arguments[0] = parser_parse_expression(parser, parser->current_token->type, scope);
	if (ast_function_call->function_call_arguments[0]->type != AST_NOOP)
		ast_function_call->function_call_arguments_count++;
	while (parser->current_token->type == TOKEN_TYPE_COMMA)
	{
		parser_advance(parser, TOKEN_TYPE_COMMA);
		ast_function_call->function_call_arguments = (ASTNode **)realloc(ast_function_call->function_call_arguments, sizeof(ASTNode *) * (ast_function_call->function_call_arguments_count + 1));
		ast_function_call->function_call_arguments[ast_function_call->function_call_arguments_count] = parser_parse_expression(parser, parser->current_token->type, scope);
		ast_function_call->function_call_arguments_count++;
	}
	ast_function_call->scope = scope;
	return (ast_function_call);
}



ASTNode	*parser_parse_variable_defination(Parser *parser, Scope *scope)
{
	parser_advance(parser, TOKEN_TYPE_KEYWORD_VAR);
	ASTNode *ast_variable_defination = ast_init(AST_VARIABLE_DEFINITION);
	ast_variable_defination->variable_defination_variable_type = parser->current_token->type - 1;
	parser_advance(parser, parser->current_token->type);
	ast_variable_defination->variable_defination_variable_name = parser->current_token->string_content;
	parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	if (parser->current_token->type == TOKEN_TYPE_SEMICOLON)
	{
		ast_variable_defination->variable_defination_value = ast_init(AST_STRING);
		ast_variable_defination->variable_defination_value->string = "(null)";
		return (ast_variable_defination);
	}
	parser_advance(parser, TOKEN_TYPE_ASSIGN);
	ast_variable_defination->variable_defination_value = parser_parse_expression(parser, ast_variable_defination->variable_defination_variable_type, scope);
	ast_variable_defination->scope = scope;
	return (ast_variable_defination);
}

ASTNode	*parser_parse_function_definition(Parser *parser, Scope *scope)
{
	parser_advance(parser, TOKEN_TYPE_KEYWORD_FUNC);
	ASTNode *ast_function_definition = ast_init(AST_FUNCTION_DEFINITION);
	ast_function_definition->function_definition_name = parser->current_token->string_content;
	parser_advance(parser, TOKEN_TYPE_IDENTIFIER);
	parser_advance(parser, TOKEN_TYPE_OPEN_PAREN);
	ast_function_definition->function_definition_arguments = (ASTNode **)calloc(sizeof(ASTNode *), 1);
	ast_function_definition->function_definition_arguments[0] = parser_parse_variable(parser, parser->current_token->type, scope);
	if (ast_function_definition->function_definition_arguments[0]->type != AST_NOOP)
		ast_function_definition->function_definition_arguments_count++;
	while (parser->current_token->type == TOKEN_TYPE_COMMA)
	{
		parser_advance(parser, TOKEN_TYPE_COMMA);
		ast_function_definition->function_definition_arguments = (ASTNode **)realloc(ast_function_definition->function_definition_arguments, sizeof(ASTNode *) * (ast_function_definition->function_definition_arguments_count + 1));
		ast_function_definition->function_definition_arguments[ast_function_definition->function_definition_arguments_count] = parser_parse_variable(parser, parser->current_token->type, scope);
		if (ast_function_definition->function_definition_arguments[ast_function_definition->function_definition_arguments_count]->type == AST_NOOP)
			break;
		ast_function_definition->function_definition_arguments_count++;
	}
	parser_advance(parser, TOKEN_TYPE_CLOSE_PAREN);
	parser_advance(parser, TOKEN_TYPE_OPEN_BRACE);
	ast_function_definition->function_definition_body = parser_parse_statements(parser, scope);
	parser_advance(parser, TOKEN_TYPE_CLOSE_BRACE);
	ast_function_definition->scope = scope;
	return (ast_function_definition);
}

ASTNode	*parser_parse_if(Parser *parser, Scope *scope)
{
	parser_advance(parser, TOKEN_TYPE_KEYWORD_IF);
	ASTNode *ast_if = ast_init(AST_IF);
	parser_advance(parser, TOKEN_TYPE_OPEN_PAREN);
	ast_if->if_condition = parser_parse_expression(parser, parser->current_token->type, scope);
	parser_advance(parser, TOKEN_TYPE_CLOSE_PAREN);
	parser_advance(parser, TOKEN_TYPE_OPEN_BRACE);
	ast_if->if_body = parser_parse_statements(parser, scope);
	parser_advance(parser, TOKEN_TYPE_CLOSE_BRACE);
	if (parser->current_token->type == TOKEN_TYPE_KEYWORD_ELSE)
	{
		parser_advance(parser, TOKEN_TYPE_KEYWORD_ELSE);
		if (parser->current_token->type == TOKEN_TYPE_KEYWORD_IF)
			ast_if->else_body = parser_parse_if(parser, scope);
		else
		{
			parser_advance(parser, TOKEN_TYPE_OPEN_BRACE);
			ast_if->else_body = parser_parse_statements(parser, scope);
			parser_advance(parser, TOKEN_TYPE_CLOSE_BRACE);
		}
	}
	else
		ast_if->else_body = ast_init(AST_NOOP);
	ast_if->scope = scope;
	return (ast_if);
}

ASTNode	*parser_parse_statement(Parser *parser, Scope *scope)
{
	TokenType type = parser->current_token->type;
	if (type == TOKEN_TYPE_KEYWORD_VAR)
		return (parser_parse_variable_defination(parser, scope));
	else if (type == TOKEN_TYPE_KEYWORD_FUNC)
		return (parser_parse_function_definition(parser, scope));
	else if (type == TOKEN_TYPE_IDENTIFIER)
		return (parser_parse_variable(parser, type, scope));
	else if (type == TOKEN_TYPE_KEYWORD_IF)
		return (parser_parse_if(parser, scope));
	return (ast_init(AST_NOOP));
}

ASTNode	*parser_parse_statements(Parser *parser, Scope *scope)
{
	ASTNode *compound = ast_init(AST_COMPOUND);
	compound->scope = scope;
	compound->compound_value = (ASTNode **)calloc(sizeof(ASTNode *), 1);
	ASTNode	*ast_statements = parser_parse_statement(parser, scope);
	if (ast_statements->type == AST_NOOP)
		return (ast_statements);
	ast_statements->scope = scope;
	compound->compound_value[0] = ast_statements;
	compound->compound_value_count++;
	while (parser->current_token->type == TOKEN_TYPE_SEMICOLON)
	{
		parser_advance(parser, TOKEN_TYPE_SEMICOLON);
		ASTNode *ast_statements = parser_parse_statement(parser, scope);
		if (ast_statements->type == AST_NOOP)
			break;
		ast_statements->scope = scope;
		compound->compound_value = (ASTNode **)realloc(compound->compound_value, sizeof(ASTNode *) * (compound->compound_value_count + 1));
		compound->compound_value[compound->compound_value_count] = ast_statements;
		compound->compound_value_count++;
	}
	return (compound);
}

ASTNode *parse(Token *tokens)
{
	Parser *parser = parser_init(tokens);
	return (parser_parse_statements(parser, parser->scope));
}
