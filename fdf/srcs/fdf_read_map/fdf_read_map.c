/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:38:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/14 15:26:16 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

t_tri_ddd	**fdf_read_map(char *name_map)
{
	t_tri_ddd	**map_tri;
	t_point_ddd	**map_points;
	int			lines;
	int			len_line;
	int			i;

	if (!fdf_check_file_extension(name_map))
		fdf_fatal_error("Wrong file extension\n", 1);
	if (!fdf_exist_file(name_map))
		fdf_fatal_error("File not found\n", 2);
	if (!fdf_file_format(name_map, &len_line, &lines))
		fdf_fatal_error("Wrong file content\n", 3);
	printf("\nlines->%d, len_lines->%d\n", lines, len_line);
	map_points = fdf_file_to_points(name_map, len_line, lines);
	map_tri = fdf_points_to_tri(map_points, len_line, lines);
	i = -1;
	while (++i < lines)
		free(map_points[i]);
	free(map_points);
	return (map_tri);
}
