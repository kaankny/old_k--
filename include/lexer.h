#ifndef LEXER_H
# define LEXER_H

#include <stdbool.h>

/*
** TOKEN TYPE ENUMERATION
*/
typedef enum {
	// Special tokens
	TOKEN_TYPE_NONE, 				// No token type
	TOKEN_TYPE_UNKNOWN, 			// Unknown token type
	TOKEN_TYPE_EOF, 				// End of file
	TOKEN_TYPE_IDENTIFIER,			// Identifier
	TOKEN_TYPE_HASH, 				// Hash (#) (used for preprocessor directives)
	// Logical operators
	TOKEN_TYPE_OPERATOR, 			// Operator
	TOKEN_TYPE_LOGICAL_AND, 		// Logical AND (&&)
	TOKEN_TYPE_LOGICAL_OR, 			// Logical OR (||)
	TOKEN_TYPE_LOGICAL_NOT, 		// Logical NOT (!)
	TOKEN_TYPE_QUESTION_MARK, 		// Question mark (?)
	// Bitwise operators
	TOKEN_TYPE_BITWISE_AND, 		// Bitwise AND (&)
	TOKEN_TYPE_BITWISE_OR, 			// Bitwise OR (|)
	TOKEN_TYPE_BITWISE_XOR, 		// Bitwise XOR (^)
	TOKEN_TYPE_BITWISE_NOT, 		// Bitwise NOT (~) 
	TOKEN_TYPE_BITWISE_SHIFT_LEFT, 	// Bitwise shift left (<<)
	TOKEN_TYPE_BITWISE_SHIFT_RIGHT, // Bitwise shift right (>>)
	// Arithmetic operators
	TOKEN_TYPE_ADD, 				// Addition (+)
	TOKEN_TYPE_SUB, 				// Subtraction (-)
	TOKEN_TYPE_MUL, 				// Multiplication (*)
	TOKEN_TYPE_DIV, 				// Division (/)
	TOKEN_TYPE_MOD, 				// Modulus (%)
	// Comparison operators
	TOKEN_TYPE_EQUAL, 				// Equal (==)
	TOKEN_TYPE_NOT_EQUAL, 			// Not equal (!=)
	TOKEN_TYPE_LESS, 				// Less than (<)
	TOKEN_TYPE_LESS_EQUAL, 			// Less than or equal (<=)
	TOKEN_TYPE_GREATER, 			// Greater than (>)
	TOKEN_TYPE_GREATER_EQUAL, 		// Greater than or equal (>=)
	// Assignment operators
	TOKEN_TYPE_ASSIGN, 				// Assignment (=)
	TOKEN_TYPE_ADD_ASSIGN, 			// Addition assignment (+=)
	TOKEN_TYPE_SUB_ASSIGN, 			// Subtraction assignment (-=)
	TOKEN_TYPE_MUL_ASSIGN, 			// Multiplication assignment (*=)
	TOKEN_TYPE_DIV_ASSIGN, 			// Division assignment (/=)
	TOKEN_TYPE_MOD_ASSIGN, 			// Modulus assignment (%=)
	TOKEN_TYPE_AND_ASSIGN, 			// Bitwise AND assignment (&=)
	TOKEN_TYPE_OR_ASSIGN, 			// Bitwise OR assignment (|=)
	TOKEN_TYPE_XOR_ASSIGN, 			// Bitwise XOR assignment (^=)
	TOKEN_TYPE_SHIFT_LEFT_ASSIGN, 	// Bitwise shift left assignment (<<=)
	TOKEN_TYPE_SHIFT_RIGHT_ASSIGN, 	// Bitwise shift right assignment (>>=)
	// Increment/decrement operators
	TOKEN_TYPE_INCREMENT, 			// Increment (++)
	TOKEN_TYPE_DECREMENT, 			// Decrement (--)
	TOKEN_TYPE_EXPONENT, 			// Exponentiation (**)
	TOKEN_TYPE_DIVISION, 			// Division (//)
	// Delimiters
	TOKEN_TYPE_COMMA, 				// Comma (,)
	TOKEN_TYPE_SEMICOLON, 			// Semicolon (;)
	TOKEN_TYPE_COLON, 				// Colon (:)
	TOKEN_TYPE_DOT, 				// Dot (.)
	TOKEN_TYPE_OPEN_PAREN, 			// Opening parenthesis (()
	TOKEN_TYPE_CLOSE_PAREN, 		// Closing parenthesis ())
	TOKEN_TYPE_OPEN_BRACE, 			// Opening brace ({)
	TOKEN_TYPE_CLOSE_BRACE, 		// Closing brace (})
	TOKEN_TYPE_OPEN_BRACKET, 		// Opening bracket ([)
	TOKEN_TYPE_CLOSE_BRACKET, 		// Closing bracket (])
	// Keywords
	TOKEN_TYPE_KEYWORD_VAR, 		// var
	TOKEN_TYPE_KEYWORD_FUNC, 		// func
	TOKEN_TYPE_KEYWORD_IF, 			// if
	TOKEN_TYPE_KEYWORD_ELSE_IF, 	// else if
	TOKEN_TYPE_KEYWORD_ELSE, 		// else
	TOKEN_TYPE_STRING, 				// String literal
	TOKEN_TYPE_KEYWORD_STRING, 		// string
	TOKEN_TYPE_CHAR, 				// Character literal (single character)
	TOKEN_TYPE_KEYWORD_CHAR, 		// char
	TOKEN_TYPE_BOOL, 				// Boolean literal (true or false)
	TOKEN_TYPE_KEYWORD_BOOL, 		// bool
	TOKEN_TYPE_NUMBER, 				// Number literal (integer)
	TOKEN_TYPE_KEYWORD_INT, 		// int
	TOKEN_TYPE_FLOAT, 				// Number literal (float)
	TOKEN_TYPE_KEYWORD_FLOAT, 		// float
}	TokenType;

/*
**	LEXER TOKEN STRUCTURE DEFINITION
*/
typedef struct s_token
{
	TokenType		type;				// Token type (identifier, number, string, etc.)
	char			*string_content;	// Token content (string)
	int				int_content;		// Token content (integer)
	float			float_content;		// Token content (float)
	char			char_content;		// Token content (character)
	unsigned int	length;				// Token length
	unsigned int	line;				// Line number
	unsigned int	column;				// Column number
	struct s_token	*next;				// Next token in the list (NULL if the last token in the list)
	struct s_token	*prev;				// Previous token in the list (NULL if the first token in the list)
}	Token;

/*
**	LEXER FUNCTION PROTOTYPES
*/
Token	*lexer_tokenize(const char *source);

#endif