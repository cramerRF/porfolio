/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:47:48 by valonso           #+#    #+#             */
/*   Updated: 2022/03/02 16:57:45 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_jump_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			return (i + 1);
	}
	return (i);
}

static int	split(char *buf, char **aux, char **memo)
{
	int	jump;
	int	buf_len;

	jump = get_jump_line(buf);
	buf_len = gnl_strlen(buf);
	if (jump == buf_len)
	{
		*aux = malloc(buf_len + 1);
		if (!(*aux))
			return (0);
		gnl_strlcpy(*aux, buf, buf_len + 1);
		return (1);
	}
	else
	{
		*aux = malloc(jump + 1);
		if (!(*aux))
			return (0);
		*memo = malloc(buf_len - jump + 1);
		if (!(*memo))
			return (0);
		gnl_strlcpy(*aux, buf, jump + 1);
		gnl_strlcpy(*memo, buf + jump, buf_len - jump + 1);
		return (1);
	}
}

static char	*get_next_line_aux(int fd, char **line, \
		char **memo, char (*read_aux)[BUFFER_SIZE + 1])
{
	char			*line_aux;

	while (read(fd, read_aux, BUFFER_SIZE))
	{
		if (!split(*read_aux, &line_aux, memo))
			return (0);
		if (*line)
			*line = gnl_strjoin(*line, line_aux);
		else
			*line = line_aux;
		if ((*line)[gnl_strlen(*line) - 1] == '\n')
			break ;
		gnl_memset(*read_aux, 0, BUFFER_SIZE + 1);
	}
	return (*line);
}

static char	*get_next_line_aux2(int fd, char **line, \
		char **memo, char (*read_aux)[BUFFER_SIZE + 1])
{
	char			*line_aux;

	gnl_strlcpy(*read_aux, *memo, gnl_strlen(*memo) + 1);
	free(*memo);
	*memo = 0;
	if (!split(*read_aux, &line_aux, memo))
		return (0);
	if (*line)
		*line = gnl_strjoin(*line, line_aux);
	else
		*line = line_aux;
	if ((*line)[gnl_strlen(*line) - 1] == '\n')
		return (*line);
	gnl_memset(*read_aux, 0, BUFFER_SIZE + 1);
	return (get_next_line_aux(fd, line, memo, read_aux));
}

char	*get_next_line(int fd)
{
	static char		*memo[4096];
	char			*line;
	char			read_aux[BUFFER_SIZE + 1];

	if (read(fd, read_aux, 0) == -1 || fd < 0 || BUFFER_SIZE < 1)
		return (0);
	gnl_memset(read_aux, 0, BUFFER_SIZE + 1);
	line = 0;
	if (!memo[fd])
		return (get_next_line_aux(fd, &line, &memo[fd], &read_aux));
	else
		return (get_next_line_aux2(fd, &line, &memo[fd], &read_aux));
}
