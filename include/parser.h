#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "lexer.h"
#include "scope.h"

typedef struct Parser
{
	Token 	*tokens;
	Token 	*current_token;
	Scope	*scope;
}	Parser;

ASTNode *parse(Token *tokens);
ASTNode	*parser_parse_funcation_call(Parser *parser, Scope *scope);
ASTNode	*parser_parse_statement(Parser *parser, Scope *scope);
ASTNode	*parser_parse_statements(Parser *parser, Scope *scope);
ASTNode	*parser_parse_variable_defination(Parser *parser, Scope *scope);
ASTNode	*parser_parse_expression(Parser *parser, TokenType type, Scope *scope);

#endif