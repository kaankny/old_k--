#include <stdio.h>

void	start_print_error()
{
	printf("\x1b[91mError\x1b[0m: \x1b[97m");
}

void	end_print_error()
{
	printf("\x1b[0m\n");
}

void	start_print_warning()
{
	printf("\x1b[93mWarning\x1b[0m: \x1b[97m");
}

void	end_print_warning()
{
	printf("\x1b[0m\n");
}

void	start_print_info()
{
	printf("\x1b[94mInfo\x1b[0m: \x1b[97m");
}

void	end_print_info()
{
	printf("\x1b[0m\n");
}

void	start_print_success()
{
	printf("\x1b[92mSuccess\x1b[0m: \x1b[97m");
}

void	end_print_success()
{
	printf("\x1b[0m\n");
}

void	start_print_debug()
{
	printf("\x1b[95mDebug\x1b[0m: \x1b[97m");
}

void	end_print_debug()
{
	printf("\x1b[0m\n");
}
