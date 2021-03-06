#include "get_next_line.h"
#include <stdio.h>

static char	*join_and_free(char **line, char *buf)
{
	char	*output;

	if (*line == NULL)
		output = ft_strdup(buf);
	// else if (*line != NULL && *buf == '\0')
	// 	output = ft_strdup(*line);
	else
		output = ft_strjoin(*line, buf);
	if (!output)
		return (NULL);
	free(*line);
	return (output);
}

// '\n''\0'

static char	*process_output(char **line)	//여기에 넘어온 문자열은 무조건 '\n'을 가지고 있음.
{
	char	*output;
	char	*backup;

	//printf("line : %s$\n", *line);
	backup = ft_strchr(*line, '\n');
	//printf("backup : %s\n", backup);
	//printf("이게안걸린다고?\n");
	if (backup == NULL)	//마지막인데 아에없이 끝나는경우랑 하나 있이 끝나는경우
	{	
		// if (ft_strlen(*line) != 0)
		// {
		// 	output = ft_strdup(*line);
		// 	printf("---> (%s)\n", output);
		// 	free(*line);	//문제발생
		// 	//printf("outputttoutputto\n");
		// 	return (output);
		// }
		//printf("---> (%s)\n", *line);
		return (NULL);
	}
	backup[0] = '\0';
	output = ft_strdup(*line);
	backup = ft_strdup(backup + 1);
	free(*line);
	if (!backup || !output)	//둘 중 하나만 NULL인데 이렇게 해도되는지
	{
		free(backup);
		free(output);
		return (NULL);
	}
	*line = backup;
	//printf("[ part 1 ]\n%s\n[ part2 ]\n%s\n", output, backup);
	return (output);
}

//그냥 전부다 읽고 ft_split으로 처리해버리면 안되나..
// char		*get_next_line(int fd)
// {
// 	static char	*line;
// 	char		*output;
// 	char		buf[BUFFER_SIZE + 1];
// 	int			read_size;

// 	*buf = '\0';
// 	//printf("lines : %s\nbuffer : %s\n", line, buf);
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (!(line && ft_strchr(line, '\n')))
// 	{
// 		//printf("HERE\n");
// 		while ((read_size = read(fd ,buf ,BUFFER_SIZE)) > 0)
// 		{
// 			if (read_size == -1)
// 				return (NULL);
// 			buf[read_size] = '\0';
// 			if (ft_strchr(buf, '\n') == NULL)
// 				break;
// 			line = join_and_free(&line, buf);
// 			if (!line)
// 				return (NULL);
// 		}
// 	}
// 	output = process_output(&line);
// 	return (output);
// }

char		*get_next_line(int fd)
{
	static char	*line;
	char		*output;
	char		buf[BUFFER_SIZE + 1];
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		read_size = read(fd ,buf ,BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		buf[read_size] = '\0';
		line = ft_strdup(buf);
		if (!line)
			return (NULL);
	}
	while (ft_strchr(line, '\n') == NULL)
	{
		read_size = read(fd ,buf ,BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		buf[read_size] = '\0';
		line = join_and_free(&line, buf);
		if (!line)
			return (NULL);
	}
	output = process_output(&line);
	return (output);
}

// int main(){
// 	char line[] = "abc\n123";
// 	char *input = ft_strdup(line);
// 	char *tmp = process_output(&input);
// }

int main()
{
	int fd;
	char *str;

	fd = open("./test2.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("fd ERROR\n");
		return (0);
	}
	while ((str = get_next_line(fd)))
	{
		printf("---------------------------\n");
		printf("main : $%s$\n", str);
		free(str);
		printf("---------------------------\n");
	}
	// printf("%s\n", str); 
	// free(str);
	close (fd);
}
