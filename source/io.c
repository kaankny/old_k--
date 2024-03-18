#include <stdlib.h>
#include "../include/memory.h"
#include "../include/utils.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_file_content(const char *file_path)
{
	FILE	*fd;
	char	*content;
	char	*buffer = NULL;

	fd = fopen(file_path, "rb");
	if (fd)
	{
		fseek(fd, 0, SEEK_END);
		long file_size = ftell(fd);
		fseek(fd, 0, SEEK_SET);
		content = (char *)calloc(file_size, file_size);
		if (content)
			fread(content, 1, file_size, fd);
		fclose(fd);
		return (content);
	}
	else
	{
		start_print_error();
		printf("File not found: %s", file_path);
		end_print_error();
		return (NULL);
	}
}

