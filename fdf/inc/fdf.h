/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:16:09 by valonso           #+#    #+#             */
/*   Updated: 2022/03/14 13:21:22 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FDF_H
# define FDF_H
/* system libs */
# include <unistd.h>
# include <stdio.h> 
# include <fcntl.h> 
# include <math.h> 
/* get_next_line */
# include "../srcs/get_next_line/get_next_line.h"
/* local libs */
# include "../libs/libft/libft.h"
/* NAME_MACOS */
# ifdef FDF_MACOS_COMPI
#  include "../libs/minilibx_macos/mlx.h"
# endif
/* NAME_LINUX */
# ifdef FDF_LINUX_COMPI
#  include "../libs/minilibx_linux/mlx.h"
#  include "../libs/minilibx_linux/mlx_int.h"
# endif
/* STRUCTS */
# include "./fdf_structs.h"
# include "./fdf_keys.h"

/* ../srcs/fdf_read_map */
t_tri_ddd	**fdf_read_map(char *name_map);
void		fdf_line_to_points(char *line, int len_line, t_point_ddd *points, int i);
t_point_ddd	**fdf_file_to_points(char *name, int len_line, int lines);
t_tri_ddd	fdf_add_tri_from_points(t_point_ddd p1, \
		 t_point_ddd p2, t_point_ddd p3);
t_tri_ddd	**fdf_points_to_tri(t_point_ddd **map_points, \
		 int len_line, int line);
void		fdf_drawtri(t_fdf *fdf, t_tri_dd tri);
/* ../srcs/fdf_read_map/fdf_read_map_checks.c */
int			fdf_file_format(char *name_map, int *len_line, int *lines);
int			fdf_check_line(char *line, int len_line);
int			fdf_check_point(char *point);
int			fdf_check_file_extension(char *name_map);
int			fdf_exist_file(char *name_map);

/* ../srcs/fdf_draw/fdf_colors.c */
int			fdf_create_trgb(int t, int r, int g, int b);
int			fdf_get_t(int trgb);
int			fdf_get_r(int trgb);
int			fdf_get_g(int trgb);
int			fdf_get_b(int trgb);

/* ./srcs/fdf_init/fdf_init.c */
void		fdf_init_all(t_fdf *fdf);

/*	./srcs/my_proyection/fdf_my_proyection.c */
int			fdf_render_next_frame_my_proyection(t_fdf *fdf);

/* ../srcs/fdf_draw/fdf_draw_utils.c */
void		fdf_put_pixel(t_fdf *fdf, int x, int y, int color);
int			fdf_parame_color(int c1, int c2, float t);

/* ../srcs/fdf_draw/fdf_draw_line_bresen.c */
void		fdf_drawline_bresen(t_fdf *fdf, t_point_dd p1, t_point_dd p2);
void		fdf_drawtri_solid(t_fdf *fdf, t_tri_dd);

/* ../srcs/fdf_hooks/fdf_hooks.c */
void		fdf_put_func_hook(t_fdf *fdf);
int			fdf_enable_hooks(int keycode, t_fdf *fdf);

/* ../srcs/fdf_utils/fdf_utils_1.c */
void		fdf_kill_split(char **split);
int			fdf_count_split(char **split);
int			fdf_bases_to_int(char *s, char *base1, char *base2, int len_base);
void    	fdf_swap_float(float *a, float *b);
/* ../srcs/fdf_main.c */
void		fdf_fatal_error(char *str, int exit_code);

/* ../srcs/algebra/alg_add.c */
t_point_ddd	alg_add_sp_ddd(t_point_ddd p1, t_point_ddd p2);
t_point_ddd	alg_sus_sp_ddd(t_point_ddd p1, t_point_ddd p2);
t_point_ddd	alg_fmul_sp_ddd(t_point_ddd p1, float k);
float		alg_dot_pro_ddd(t_point_ddd p1, t_point_ddd p2);
t_point_ddd	alg_norma_sp_ddd(t_point_ddd p);

#endif
