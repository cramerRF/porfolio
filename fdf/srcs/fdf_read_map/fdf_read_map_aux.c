/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:38:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/22 18:09:17 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int		fdf_get_pos_base(char c, char *b1, char *b2, int b_len)
{
	int	i;

	i = 0;
	while (c != b1[i] && i < b_len)
		i++;
	if (i == b_len)
	{
		i = 0;
		while (c != b2[i] && i < b_len)
			i++;
		if (i == b_len)
			return (0);
	}
	return (i);
}

int		fdf_get_color_file(char *s, char *b1, char *b2, int base_len)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = 0;
	r = 0;
	g = 0;
	b = 0;
	if (ft_strlen(s) == 2)
	{
		b = fdf_get_pos_base(s[0], b1, b2, base_len) * base_len + fdf_get_pos_base(s[1], b1, b2, base_len);
	}
	if (ft_strlen(s) == 4)
	{
		g = fdf_get_pos_base(s[0], b1, b2, base_len) * base_len + fdf_get_pos_base(s[1], b1, b2, base_len);
		r = fdf_get_pos_base(s[2], b1, b2, base_len) * base_len + fdf_get_pos_base(s[3], b1, b2, base_len);
	}
	if (ft_strlen(s) == 6)
	{
		r = fdf_get_pos_base(s[0], b1, b2, base_len) * base_len + fdf_get_pos_base(s[1], b1, b2, base_len);
		g = fdf_get_pos_base(s[2], b1, b2, base_len) * base_len + fdf_get_pos_base(s[3], b1, b2, base_len);
		b = fdf_get_pos_base(s[4], b1, b2, base_len) * base_len + fdf_get_pos_base(s[5], b1, b2, base_len);	
	}
	if (ft_strlen(s) == 8)
	{
		b = fdf_get_pos_base(s[0], b1, b2, base_len) * base_len + fdf_get_pos_base(s[1], b1, b2, base_len);
		g = fdf_get_pos_base(s[2], b1, b2, base_len) * base_len + fdf_get_pos_base(s[3], b1, b2, base_len);
		r = fdf_get_pos_base(s[4], b1, b2, base_len) * base_len + fdf_get_pos_base(s[5], b1, b2, base_len);	
		t = fdf_get_pos_base(s[6], b1, b2, base_len) * base_len + fdf_get_pos_base(s[7], b1, b2, base_len);
	}
	return (fdf_create_trgb(t, r, g, b));
}


void	fdf_line_to_points(char *line, int len_line, t_point_ddd *points, int i)
{
	char	**line_split;
	int		j;
	int		k;

	printf("Reading line %d\n\033[2J", i);
	line_split = ft_split(line, ' ');
	j = -1;
	while (line_split[++j])
	{
		//printf("x = %d, y = %d, line_split %s\n", i, j, line_split[j]);
		points[j].x = i * 4;
		points[j].y = j * 4;
		points[j].z = ft_atoi(line_split[j]);
		//printf("x = %d, y = %d, line_split %s\n", i, j, line_split[j]);
		k = 0;
		while (line_split[j][k] != '\0' && line_split[j][k] != ',')
			k++;
		//printf("k = %d\n", k);
		if (line_split[j][k] == ',')
		{
			int	aux_color;

			//printf("char -> %s\n", line_split[j] + k + 3);
			aux_color = fdf_get_color_file(line_split[j] + k + 3, \
						"0123456789abcdef", "0123456789ABCDEF", 16);
			//printf("color -> %d\n",  aux_color);
			points[j].color = aux_color;
		}
		else
		{
			/*
			if (points[j].z < 5.0f)
				points[j].color = fdf_create_trgb(0, 0, 0, 255);
			else if (points[j].z > 10.0f)
				points[j].color = fdf_create_trgb(0, 255, 0, 0);
			else
				points[j].color = fdf_create_trgb(0, 255, 255, 255);
			*/
			points[j].color = 0x00FF0000;
		}
			//points[j].color = 0x00FFFFFF;
	}
	fdf_kill_split(line_split);
}

t_point_ddd	**fdf_file_to_points(char *name, int len_line, int lines)
{
	int			fd;
	t_point_ddd	**sol;
	int			i;
	char		*line;

	fd = open(name, O_RDONLY);
	sol = malloc(lines * 8);
	i = -1;
	while (++i < lines)
		sol[i] = malloc(len_line * sizeof(t_point_ddd));
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		i++;
		fdf_line_to_points(line, len_line, sol[i], i);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (sol);
}

t_tri_ddd	fdf_add_tri_from_points(t_point_ddd p1, \
		t_point_ddd p2, t_point_ddd p3)
{
	t_tri_ddd	tri;

	tri.tag = 1;
	tri.p1 = p1;
	tri.p2 = p2;
	tri.p3 = p3;
	return (tri);
}

static void	fdf_points_to_tri_aux(t_point_ddd **map_points, \
		int len_line, int line, t_tri_ddd **map_tri)
{
	int	i;
	int	j;

	i = -1;
	while (++i < line - 1)
	{
		j = -1;
		while (++j < len_line - 1)
		{
			map_tri[i][j] = fdf_add_tri_from_points(map_points[i][j], \
					map_points[i + 1][j], map_points[i][j + 1]);
		}
		map_tri[i][j] = fdf_add_tri_from_points(map_points[i][j], \
				map_points[i + 1][j], map_points[i + 1][j - 1]);
	}
}

t_tri_ddd	**fdf_points_to_tri(t_point_ddd **map_points, \
		int len_line, int line)
{
	t_tri_ddd	**map_tri;
	int			i;
	int			j;

	map_tri = malloc((line + 1) * 8);
	map_tri[line] = NULL;
	i = -1;
	while (++i < line)
	{
		map_tri[i] = malloc((len_line + 1) * sizeof(t_tri_ddd));
		map_tri[i][len_line].tag = 0;
	}
	fdf_points_to_tri_aux(map_points, len_line, line, map_tri);
	i--;
	map_tri[i][len_line - 1].tag = 0;
	j = -1;
	while (++j < len_line - 1)
		map_tri[i][j] = fdf_add_tri_from_points(map_points[i][j], \
				map_points[i][j + 1], map_points[i - 1][j + 1]);
	return (map_tri);
}
