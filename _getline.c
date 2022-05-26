#include "main.h"
#include "unistd.h"
#include <stdlib.h>
#include <stdio.h>

/**
 *_getline - get the next line from a file
 *@line: A pointer
 *@line_len: A ponter to size
 *@fd: file descriptor
 *
 *Return: A string
 */
ssize_t _getline(char **line, size_t *line_len, int fd)
{
	static char chk[32];
	static ssize_t n;
	static size_t i;
	ssize_t len = 0, max_len = *line_len;

	if (*line == NULL)
	{
		max_len = sizeof(chk);
		*line = malloc(sizeof(**line) * max_len);
	}
	while (1)
	{
		if (n > 0)
		{
			while (n-- > 0)
				(*line)[len++] = chk[i++];
			if (chk[i - 1] == '\n' || i < sizeof(chk))
				break;
		}
		i = 0;
		n = read(fd, chk, sizeof(chk));
		if (n > max_len - len)
		{
			max_len += sizeof(chk);
			*line = _realloc(*line, (max_len + 1));
		}
	}
	(*line)[len] = '\0';
	*line_len = max_len;
	return (len);
}

