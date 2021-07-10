#include "get_next_line.h"
#include <stdio.h>

static int	trim_output(char **output, char **backup)
{
	char	*tmp;
	char	*op_addr;

	tmp = ft_strchr(*output, '\n');
	if (!tmp)
	{
		op_addr = *output;
		free(*backup);
		*backup = ft_strdup(tmp + 1);
		*tmp = '\0';
		*output = ft_strdup(*output);
		free(op_addr);
		if (!(*output) || !(*backup))
		{
			free(*output);
			free(*backup);
			return (0);
		}
	}
	return (1);
}

char		*get_next_line(int fd)
{
	static char	*backup;
	char		*output;
	char		buf[BUFFER_SIZE + 1];
	int			read_size;

	printf("test\n");

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);	
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (!backup)
			output = ft_strjoin(backup, buf);
		else
			output = ft_strdup(buf);
		if (!output)
		{
			free(backup);
			return (NULL);
		}
	}
	if (read_size == -1)
		return (NULL);
	if (trim_output(&output, &backup) == 0)
		return (NULL);
	return (output);
}

int main()
{
	int fd;
	char *str;

	fd = open("./test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("fd ERROR\n");
		return (0);
	}
	while (!(str = get_next_line(fd)))
	{
		printf("%s\n", str);
		free(str);
	}
	printf("%s\n", str);
	free(str);
	close (fd);
}
