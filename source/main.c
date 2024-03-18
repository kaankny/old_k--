#include "../include/lexer.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/AST.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/time.h"
#include <stdio.h>

/*
**	TODO LIST: 
**	kaçış karakterleri ekle
**	fonksiyon çağırmada argümanlar +, , gibi operatörlerle birleştirilebilsin
*/

void	print_ast(ASTNode *ast)
{
	int i = 0;
	printf("Compound value count: %d\n", ast->compound_value_count);
	while (i < ast->compound_value_count)
	{
		if (ast->compound_value[i]->type == AST_VARIABLE_DEFINITION)
		{
			printf("Variable definition: %s\n", ast->compound_value[i]->variable_defination_variable_name);
			printf("Variable type: %d\n", ast->compound_value[i]->variable_defination_variable_type);
			printf("Variable value: %s\n", ast->compound_value[i]->variable_defination_value->string);
		}
		else if (ast->compound_value[i]->type == AST_FUNCTION_DEFINITION)
		{
			printf("Function definition: %s\n", ast->compound_value[i]->function_call_name);
		}
		else if (ast->compound_value[i]->type == AST_FUNCTION_CALL)
		{
			printf("Function call: %s\n", ast->compound_value[i]->function_call_name);
			printf("Function call arguments count: %d\n", ast->compound_value[i]->function_call_arguments_count);
			int j = 0;
			while (j < ast->compound_value[i]->function_call_arguments_count)
			{
				if (ast->compound_value[i]->function_call_arguments[j]->type == AST_STRING)
					printf("Function call argumen string: %s\n", ast->compound_value[i]->function_call_arguments[j]->string);
				else if (ast->compound_value[i]->function_call_arguments[j]->type == AST_VARIABLE)
					printf("Function call argument variable: %s\n", ast->compound_value[i]->function_call_arguments[j]->variable_name);
				else if (ast->compound_value[i]->function_call_arguments[j]->type == AST_COMPOUND)
					printf("Function call argument: Compound\n");
				j++;
			}
		}
		else if (ast->compound_value[i]->type == AST_VARIABLE)
		{
			printf("Variable: %s\n", ast->compound_value[i]->variable_name);
		}
		else if (ast->compound_value[i]->type == AST_COMPOUND)
		{
			printf("Compound\n");
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	start_timer();
	char	*code = get_file_content(argv[1]); // NULL gelme durumunu kontrol et
	Token	*tokens;

	tokens = lexer_tokenize(code);
	ASTNode *ast = parse(tokens);
	//print_ast(ast);
	Interpreter *interpreter = interpreter_init();
	interpreter_visit(interpreter, ast);
	free_memory();
	return (0);
}
