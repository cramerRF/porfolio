/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:20:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/22 18:01:25 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

typedef struct s_point_dd
{
	float	x;
	float	y;
	int		color;
}	t_point_dd;

typedef struct s_point_ddd
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point_ddd;

typedef struct s_tri_dd
{
    int         tag;
	float       dist;
    t_point_dd	p1;
	t_point_dd	p2;
	t_point_dd	p3;
}	t_tri_dd;

typedef struct s_tri_ddd
{
    int         tag;
	t_point_ddd	p1;
	t_point_ddd	p2;
	t_point_ddd	p3;
}	t_tri_ddd;

typedef struct	s_cam
{
	t_point_ddd	pos;
	t_point_ddd	nor;
	t_point_ddd	up;
	t_point_ddd left;
	float		focus;
	float		zoom;
}	t_cam;

typedef struct	s_fdf
{
	int			k_z;
	int			k_xy;
	t_tri_ddd	**map;
	t_tri_dd	**map_dd;
	int			map_size[2];
	t_cam		cam;
	float		rot[3][3];
    int			(*func_hook[512])(void *);
	int         witdh;
    int         height;
    int         bits_per_pixel;
    int         line_lenght;
    int         endian;
    void        *mlx;
    void        *win;
    void        *img;
    void        *addr;
}	t_fdf;

#endif
