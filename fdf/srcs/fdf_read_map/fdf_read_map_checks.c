/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:38:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/04 04:05:10 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	fdf_exist_file(char *name_map)
{
	int	fd;
	int	rt;

	fd = open(name_map, O_RDONLY);
	if (fd != -1)
	{
		rt = 1;
		close(fd);
	}
	else
		rt = 0;
	return (rt);
}

int	fdf_check_file_extension(char *name_map)
{
	int	i;

	i = ft_strlen(name_map);
	if (ft_strncmp(name_map + i - 4, ".fdf", 4))
		return (0);
	return (1);
}

int	fdf_check_point(char *point)
{
	int	i;

	i = 0;
	if (point[i] == '-' || point[i] == '+')
		i++;
	while (point[i] <= '9' && point[i] >= '0')
		i++;
	if (point[i] == 0)
		return (1);
	else if (point[i] == ',')
	{
		if (!(point[i + 1] == '0' && point[i + 2] == 'x'))
			return (0);
		i += 3;
		while ((point[i] <= '9' && point[i] >= '0') || \
				(point[i] <= 'F' && point[i] >= 'A') || \
				(point[i] <= 'f' && point[i] >= 'a'))
			i++;
		if (point[i] == '\0')
			return (1);
	}
	return (0);
}

int	fdf_check_line(char *line, int len_line)
{
	char	**split_line;
	int		i;

	split_line = ft_split(line, ' ');
	if (len_line != fdf_count_split(split_line))
	{
		fdf_kill_split(split_line);
		return (0);
	}
	i = -1;
	while (++i < len_line - 1)
	{
		if (!fdf_check_point(split_line[i]))
		{
			fdf_kill_split(split_line);
			return (0);
		}
	}
	fdf_kill_split(split_line);
	return (1);
}

int	fdf_file_format(char *name_map, int *len_line, int *lines)
{
	int		fd;
	char	*line;
	char	**split_line;

	*lines = 0;
	fd = open(name_map, O_RDONLY);
	line = get_next_line(fd);
	split_line = ft_split(line, ' ');
	*len_line = fdf_count_split(split_line);
	fdf_kill_split(split_line);
	while (line)
	{
		if (!fdf_check_line(line, *len_line))
		{
			free(line);
			return (0);
		}
		printf("Checking line %d\n\033[2J", ++(*lines));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
