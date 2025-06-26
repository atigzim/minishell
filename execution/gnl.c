#include "../minishell.h"

char	*ft_readline(int bytes, char *line, int fd)
{
	char	*buf;
	char	*tmp;

	buf = malloc(2);
	if (!buf)
		return (NULL);
	bytes = read(fd, &buf[0], 1);
	if (bytes <= 0)
		return (free(buf), NULL);
	buf[1] = '\0';
	line = ft_strjoin(line, buf);
	while (bytes > 0 && *buf != '\n')
	{
		bytes = read(fd, &buf[0], 1);
		if (bytes <= 0)
			return (free(buf), line);
		buf[1] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
        // printf("-------> %s", line);
		free(tmp);
	}
	if (buf)
		free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	int (bytes);
	if (fd < 0)
		return (NULL);
	bytes = 0;
	line = ft_readline(bytes, NULL, fd);
	return (line);
}