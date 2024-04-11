#include "../include/lexer.h"
#include "../include/utils.h"
#include <stdlib.h>
#include "../include/memory.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/time.h"

void	lexer_add_token(Token **tokens, TokenType type,
	char *string_content, int int_content, float float_content, char char_content,
	unsigned int length, unsigned int line, unsigned int column)
{
	Token *token = (Token *)malloc(sizeof(Token));
	token->type = type;
	token->string_content  = string_content;
	token->int_content = int_content;
	token->float_content = float_content;
	token->char_content = char_content;
	token->length = length;
	token->line = line;
	token->column = column;
	token->next = NULL;
	token->prev = NULL;
	if (*tokens)
	{
		Token *last = *tokens;
		while (last->next)
			last = last->next;
		last->next = token;
		token->prev = last;
	}
	else
		*tokens = token;
}

bool	isoperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>' || c == '!' || c == '&' || c == '|' || c == '^' || c == '~' || c == '?' || c == ':' || c == ',' || c == ';' || c == '.' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '\\' || c == '#' || c == '@' || c == '$' || c == '`')
		return (true);
	return (false);
}

Token	*lexer_tokenize(const char *source)
{
	Token *tokens = NULL;
	unsigned int line = 1;
	unsigned int column = 1;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int length = 0;
	char *buffer = NULL;
	bool is_all_digit = false;

	while (source[i])
	{
		if (isspace(source[i])) // SKIP WHITESPACES
		{
			if (source[i] == '\n')
			{
				line++;
				column = 1;
			}
			else
				column++;
			i++;
		}
		else if (source[i] == '/' && source[i + 1] == '*')
		{
			i += 2;
			while (source[i] && !(source[i] == '*' && source[i + 1] == '/'))
			{
				if (source[i] == '\n')
				{
					line++;
					column = 1;
				}
				else
					column++;
				i++;
			}
			if (!source[i])
			{
				start_print_error();
				printf("Unterminated comment (line: %d, column: %d)", line, column);
				end_print_error();
				free_memory();
				exit(1);
			}
			i += 2;
		}
		else if (source[i] == '/' && source[i + 1] == '/')
		{
			while (source[i] && source[i] != '\n')
				i++;
			if (!source[i])
				break;
			line++;
			column = 1;
			i++;
		}
		else if (isdigit(source[i])) // NUMBER
		{
			is_all_digit = true;
			j = i;
			while (isdigit(source[j]))
				j++;
			if (source[j] == '.')
			{
				j++;
				while (isdigit(source[j]))
					j++;
			}
			length = j - i;
			buffer = (char *)malloc(length + 1);
			strncpy(buffer, source + i, length);
			buffer[length] = '\0';
			i = -1;
			bool is_float  = false;
			while (buffer[++i])
				if (!isdigit(buffer[i]))
				{
					if (buffer[i] == '.')
						is_float = true;
					is_all_digit = false;
					break;
				}
			if (is_all_digit)
				lexer_add_token(&tokens, TOKEN_TYPE_NUMBER, buffer, atoi(buffer), atof(buffer), '\0', length, line, column);
			else
			{
				start_print_error();
				printf("Invalid number '%s' (line: %d, column: %d)", buffer, line, column);
				end_print_error();
				free_memory();
				exit(1);
			}
			i = j;
			column += length;
		}
		else if (isalnum(source[i])) // IDENTIFIER OR KEYWORD
		{
			is_all_digit = true;
			j = i;
			while (isalnum(source[j]))
				j++;
			length = j - i;
			buffer = (char *)malloc(length + 1);
			strncpy(buffer, source + i, length);
			buffer[length] = '\0';
			i = -1;
			while (buffer[++i])
				if (!isdigit(buffer[i]))
				{
					is_all_digit = false;
					break;
				}
			if (is_all_digit)
				lexer_add_token(&tokens, TOKEN_TYPE_NUMBER, buffer, atoi(buffer), atof(buffer), '\0', length, line, column);
			else
			{
				// TODO: keywordlerin kontrolu yapilacak
				if (strcmp(buffer, "var") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_VAR, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "func") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_FUNC, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "if") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_IF, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "else") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_ELSE, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "elseif") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_ELSE_IF, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "char") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_CHAR, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "int") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_INT, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "float") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_FLOAT, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "string") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_STRING, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "bool") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_KEYWORD_BOOL, buffer, 0, 0, '\0', length, line, column);
				else if (strcmp(buffer, "true") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_BOOL, buffer, 1, 0, '\0', length, line, column);
				else if (strcmp(buffer, "false") == 0)
					lexer_add_token(&tokens, TOKEN_TYPE_BOOL, buffer, 0, 0, '\0', length, line, column);
				else
					lexer_add_token(&tokens, TOKEN_TYPE_IDENTIFIER, buffer, 0, 0, '\0', length, line, column);
			}
			i = j;
			column += length;
		}
		else if (source[i] == '"') // STRING LITERAL
		{
			j = i + 1;
			while (source[j] && source[j] != '"' && source[j] != '\n')
				j++;
			if (!source[j] || source[j] == '\n')
			{
				start_print_error();
				printf("Unterminated string literal (line: %d, column: %d)", line, column);
				end_print_error();
				free_memory();
				exit(1);
			}
			length = j - i;
			buffer = (char *)malloc(length + 1);
			strncpy(buffer, source + i + 1, length - 1);
			buffer[length - 1] = '\0';
			lexer_add_token(&tokens, TOKEN_TYPE_STRING, buffer, 0, 0, '\0', length, line, column);
			i = j + 1;
			column += length;
		}
		else if (source[i] == '\'') // CHAR LITERAL
		{
			j = i + 1;
			while (source[j] && source[j] != '\'' && source[j] != '\n')
				j++;
			if (!source[j] || source[j] == '\n')
			{
				start_print_error();
				printf("Unterminated character literal (line: %d, column: %d)", line, column);
				end_print_error();
				free_memory();
				exit(1);
			}
			length = j - i;
			buffer = (char *)malloc(length + 1);
			strncpy(buffer, source + i + 1, length - 1);
			buffer[length - 1] = '\0';
			if (length != 2)
			{
				start_print_warning();
				printf("Character literal must contain exactly one character (line: %d, column: %d) (found %d characters)",
					line, column, length - 1);
				end_print_warning();
				start_print_info();
				printf("Character literal will be truncated to '%c'", buffer[0]);
				end_print_info();
			}
			lexer_add_token(&tokens, TOKEN_TYPE_CHAR, buffer, buffer[0], 0, buffer[0], length, line, column);
			i = j + 1;
			column += length;
		}
		else if (isoperator(source[i])) // OPERATOR
		{
			if (source[i] == ':')
			{
				if (source[i + 1] == '=')
				{
					lexer_add_token(&tokens, TOKEN_TYPE_ASSIGN, ":=", 0, 0, '\0', 2, line, column);
					i += 2;
					column += 2;
				}
				else
				{
					lexer_add_token(&tokens, TOKEN_TYPE_COLON, ":", 0, 0, '\0', 1, line, column);
					i++;
					column++;
				}
			}
			else if (source[i] == ';')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_SEMICOLON, ";", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '(')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_OPEN_PAREN, "(", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '=')
			{
				if (source[i + 1] == '=')
				{
					lexer_add_token(&tokens, TOKEN_TYPE_EQUAL, "==", 0, 0, '\0', 2, line, column);
					i += 2;
					column += 2;
				}
				else
				{
					lexer_add_token(&tokens, TOKEN_TYPE_ASSIGN, "=", 0, 0, '\0', 1, line, column);
					i++;
					column++;
				}
			}
			else if (source[i] == ',')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_COMMA, ",", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '{')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_OPEN_BRACE, "{", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '}')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_CLOSE_BRACE, "}", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '[')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_OPEN_BRACKET, "[", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == ']')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_CLOSE_BRACKET, "]", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == ')')
			{
				lexer_add_token(&tokens, TOKEN_TYPE_CLOSE_PAREN, ")", 0, 0, '\0', 1, line, column);
				i++;
				column++;
			}
			else if (source[i] == '+')
			{
				if (source[i + 1] == '+')
				{
					lexer_add_token(&tokens, TOKEN_TYPE_INCREMENT, "++", 0, 0, '\0', 2, line, column);
					i += 2;
					column += 2;
				}
				else if (source[i + 1] == '=')
				{
					lexer_add_token(&tokens, TOKEN_TYPE_ADD_ASSIGN, "+=", 0, 0, '\0', 2, line, column);
					i += 2;
					column += 2;
				}
				else
				{
					lexer_add_token(&tokens, TOKEN_TYPE_ADD, "+", 0, 0, '\0', 1, line, column);
					i++;
					column++;
				}
			}
			else
				i++;
		}
		else // UNKNOWN CHARACTER
		{
			start_print_error();
			printf("Unknown character '%c' (line: %d, column: %d)", source[i], line, column);
			end_print_error();
			free_memory();
			exit(1);
		}
	}
	lexer_add_token(&tokens, TOKEN_TYPE_EOF, "EOF", 0, 0, '\0', 3, line, column);
	return (tokens);
}
