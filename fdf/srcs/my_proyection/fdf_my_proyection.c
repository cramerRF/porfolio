/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:35:35 by valonso           #+#    #+#             */
/*   Updated: 2022/06/28 23:42:36 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"
#include <time.h>

t_point_ddd	fdf_cross_product(t_point_ddd p1, t_point_ddd p2)
{
	t_point_ddd	sol;
	float		mod;

	sol.x = p1.y * p2.z - p1.z * p2.y;
	sol.y = p1.z * p2.x - p1.x * p2.z;
	sol.z = p1.x * p2.y - p1.y * p2.x;
	mod = sqrt(sol.x * sol.x + sol.y * sol.y + sol.z * sol.z);
	sol.x /= mod;
	sol.y /= mod;
	sol.z /= mod;
	return (sol);
}

void	fdf_get_frames(t_fdf *fdf)
{
	static int	ts;
	static int	frames;
	char		*aux;

	if (ts != time(NULL))
	{
		aux = ft_itoa(frames);
		mlx_string_put(fdf->mlx, fdf->win, 10, 10, 0x0000FF00, aux);
		free(aux);
		ts = time(NULL);
		frames = 0;
	}
	else
		frames++;
}

t_point_ddd	fdf_middle_point(t_point_ddd p1, t_point_ddd p2)
{
	t_point_ddd	sol;

	sol.x = (p1.x + p2.x) / 2;
	sol.y = (p1.y + p2.y) / 2;
	sol.z = (p1.z + p2.z) / 2;
	return (sol);
}

float	fdf_dist_bari_point(t_tri_ddd tri, t_point_ddd p)
{
	t_point_ddd	bari;
	t_point_ddd	delta;

	bari = fdf_middle_point(tri.p1, tri.p2);
	bari = fdf_middle_point(bari, tri.p3);
	delta.x = bari.x - p.x;
	delta.y = bari.y - p.y;
	delta.z = bari.z - p.z;
	return (sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z));
}

t_tri_ddd	fdf_translation_to_cam(t_tri_ddd ori_tri, t_point_ddd cam_pos)
{
	t_tri_ddd	tri;

	tri.p1.x = ori_tri.p1.x - cam_pos.x;
	tri.p1.y = ori_tri.p1.y - cam_pos.y;
	tri.p1.z = ori_tri.p1.z - cam_pos.z;
	tri.p1.color = ori_tri.p1.color;
	tri.p2.x = ori_tri.p2.x - cam_pos.x;
	tri.p2.y = ori_tri.p2.y - cam_pos.y;
	tri.p2.z = ori_tri.p2.z - cam_pos.z;
	tri.p2.color = ori_tri.p2.color;
	tri.p3.x = ori_tri.p3.x - cam_pos.x;
	tri.p3.y = ori_tri.p3.y - cam_pos.y;
	tri.p3.z = ori_tri.p3.z - cam_pos.z;
	tri.p3.color = ori_tri.p3.color;
	return (tri);
}

t_point_ddd	fdf_mult_mat_vector(float mat[3][3], t_point_ddd v)
{
	t_point_ddd	sol;

	sol.x = mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z;
	sol.y = mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z;
	sol.z = mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z;
	sol.color = v.color;
	return (sol);
}

t_tri_ddd	fdf_rotation_to_cam(t_tri_ddd ori_tri, t_fdf *fdf)
{
	t_tri_ddd	tri;

	tri.p1 = fdf_mult_mat_vector(fdf->rot, ori_tri.p1);
	tri.p2 = fdf_mult_mat_vector(fdf->rot, ori_tri.p2);
	tri.p3 = fdf_mult_mat_vector(fdf->rot, ori_tri.p3);
	return (tri);
}

t_tri_dd	fdf_intersection_cam(t_tri_ddd ori_tri, t_fdf *fdf)
{
	t_tri_dd	tri;

	tri.p1.x = ori_tri.p1.x;
	tri.p1.y = ori_tri.p1.y;
	tri.p1.color = ori_tri.p1.color;
	tri.p2.x = ori_tri.p2.x;
	tri.p2.y = ori_tri.p2.y;
	tri.p2.color = ori_tri.p2.color;
	tri.p3.x = ori_tri.p3.x;
	tri.p3.y = ori_tri.p3.y;
	tri.p3.color = ori_tri.p3.color;
	return (tri);
}

t_point_ddd fdf_inter_plane_line(t_point_ddd lp, t_fdf *fdf)
{
	float		t;
	t_point_ddd	aux;

	t = lp.x / (lp.x + (fdf->cam).focus);
	aux.x = -(fdf->cam).focus;
	aux.y = 0;
	aux.z = 0;
	aux = alg_sus_sp_ddd(lp, aux);
	return (alg_add_sp_ddd(lp, alg_fmul_sp_ddd(aux, t)));
}

t_tri_dd	fdf_intersection_cam_v2(t_tri_ddd ori_tri, t_fdf *fdf)
{
	t_tri_ddd	tri_ddd;
	t_tri_dd	tri;
	
	tri_ddd.p1 = fdf_inter_plane_line(ori_tri.p1, fdf);
	tri_ddd.p2 = fdf_inter_plane_line(ori_tri.p2, fdf);
	tri_ddd.p3 = fdf_inter_plane_line(ori_tri.p3, fdf);
	tri.p1.x = tri_ddd.p1.z;
	tri.p1.y = tri_ddd.p1.y;
	tri.p1.color = ori_tri.p1.color;
	tri.p2.x = tri_ddd.p2.z;
	tri.p2.y = tri_ddd.p2.y;
	tri.p2.color = ori_tri.p2.color;
	tri.p3.x = tri_ddd.p3.z;
	tri.p3.y = tri_ddd.p3.y;
	tri.p3.color = ori_tri.p3.color;
	return (tri);
}

t_tri_dd	fdf_expansion(t_tri_dd tri, t_fdf *fdf, float k)
{
	tri.p1.x *= k;
	tri.p1.y *= k;
	tri.p2.x *= k;
	tri.p2.y *= k;
	tri.p3.x *= k;
	tri.p3.y *= k;
	return (tri);
}

t_tri_dd	fdf_plane_to_screen(t_tri_dd tri_dd, t_fdf *fdf)
{
	tri_dd.p1.x += (float) fdf->witdh / 2.0f;
	tri_dd.p1.y += (float) fdf->height / 2.0f;
	tri_dd.p2.x += (float) fdf->witdh / 2.0f;
	tri_dd.p2.y += (float) fdf->height / 2.0f;
	tri_dd.p3.x += (float) fdf->witdh / 2.0f;
	tri_dd.p3.y += (float) fdf->height / 2.0f;
	return (tri_dd);
}

float	fdf_angle_btw_ddd(t_point_ddd p1, t_point_ddd p2)
{
	return ((alg_dot_pro_ddd(p1, p2) / \
			(sqrt(alg_dot_pro_ddd(p1, p1)) * \
			sqrt(alg_dot_pro_ddd(p2, p2)))));
}

t_tri_ddd	fdf_noise(t_tri_ddd ori, float n)
{
	static t_tri_ddd	tri;

	if (time(NULL) % 2 == 0)
	{
		tri = ori;
		tri.p1.x += (float)(rand() % (int) n) / n;
		tri.p1.y += (float)(rand() % (int) n) / n;
		tri.p1.z += (float)(rand() % (int) n) / n;
		tri.p2.x += (float)(rand() % (int) n) / n;
		tri.p2.y += (float)(rand() % (int) n) / n;
		tri.p2.z += (float)(rand() % (int) n) / n;
		tri.p3.x += (float)(rand() % (int) n) / n;
		tri.p3.y += (float)(rand() % (int) n) / n;
		tri.p3.z += (float)(rand() % (int) n) / n;
	}
	return (tri);
}

void	fdf_proyect_tri(t_tri_ddd ori_tri, t_fdf *fdf)
{
	t_tri_ddd	tri_ddd;
	t_tri_dd	tri_dd;
	t_point_ddd	p_ddd;

	/*
	if (alg_dot_pro_ddd(fdf->cam.nor, alg_sus_sp_ddd(ori_tri.p1, \
		fdf->cam.pos)) < 0.01f || alg_dot_pro_ddd(fdf->cam.nor, \
		alg_sus_sp_ddd(ori_tri.p2, fdf->cam.pos)) < 0.01f || \
		alg_dot_pro_ddd(fdf->cam.nor, \
		alg_sus_sp_ddd(ori_tri.p3, fdf->cam.pos)) < 0.01f)
		return ;
	*/
	tri_ddd = ori_tri;
	p_ddd = fdf_mult_mat_vector(fdf->rot, fdf->cam.pos);
	tri_ddd = fdf_translation_to_cam(tri_ddd, fdf->cam.pos);
	tri_ddd = fdf_translation_to_cam(tri_ddd, p_ddd);
	tri_ddd = fdf_rotation_to_cam(tri_ddd, fdf);
	tri_dd = fdf_intersection_cam(tri_ddd, fdf);
	tri_dd = fdf_expansion(tri_dd, fdf, fdf->cam.zoom);
	tri_dd = fdf_plane_to_screen(tri_dd, fdf);
	/*if ((tri_dd.p1.x < fdf->witdh && tri_dd.p1.x > 0 && tri_dd.p1.y > 0 \
	&& tri_dd.p1.y < fdf->height) || (tri_dd.p2.x < fdf->witdh && \
	tri_dd.p2.x > 0 && tri_dd.p2.y > 0 && tri_dd.p2.y < fdf->height) \
	|| (tri_dd.p3.x < fdf->witdh && tri_dd.p3.x > 0 && \
	tri_dd.p3.y > 0 && tri_dd.p3.y < fdf->height))
	*/	
	fdf_drawtri(fdf, tri_dd);
}

void	fdf_proyect_all_tri(t_fdf *fdf)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (fdf->map[++i])
	{
		j = -1;
		while (fdf->map[i][++j].tag)
			fdf_proyect_tri(fdf->map[i][j], fdf);
	}
}

void	fdf_order_tri(t_fdf *fdf)
{
	return ;
}

void	fdf_draw_all_tri(t_fdf *fdf)
{
	int		i;

	i = -1;
	while (fdf->map_dd[++i])
		fdf_drawtri_solid(fdf, *fdf->map_dd[i]);
}

void	fdf_set_rotation(t_fdf *fdf)
{
	float	mat[3][3];
	float	det;
	int		i;
	int		j;

	det = 0;
	mat[0][0] = fdf->cam.nor.x;
	mat[0][1] = fdf->cam.nor.y;
	mat[0][2] = fdf->cam.nor.z;
	mat[1][0] = fdf->cam.up.x;
	mat[1][1] = fdf->cam.up.y;
	mat[1][2] = fdf->cam.up.z;
	mat[2][0] = fdf->cam.left.x;
	mat[2][1] = fdf->cam.left.y;
	mat[2][2] = fdf->cam.left.z;
	i = -1;
	while (++i < 3)
		det += mat[0][i] * (mat[1][(i + 1) % 3] * \
				mat[2][(i + 2) % 3] - mat[1][(i + 2) % 3] * mat[2][(i + 1) % 3]);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			fdf->rot[i][j] = (mat[(j + 1) % 3][(i + 1) % 3] * \
					mat[(j + 2) % 3][(i + 2) % 3] - mat[(j + 1) % 3][(i + 2) % 3] * \
					mat[(j + 2) % 3][(i + 1) % 3]) / det;
	}
}

int	fdf_print_cam(t_fdf *fdf);

int	fdf_render_next_frame_my_proyection(t_fdf *fdf)
{
	//fdf->cam.up = fdf_cross_product(fdf->cam.left, fdf->cam.nor);
	//fdf->cam.left = fdf_cross_product(fdf->cam.nor, fdf->cam.up);
	//fdf_print_cam(fdf);
	fdf_set_rotation(fdf);
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, fdf->witdh, fdf->height);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
	//printf("proyecting all tring\n");
	fdf_proyect_all_tri(fdf); //
	//fdf_order_tri(fdf); //
	//fdf_draw_all_tri(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_get_frames(fdf);
	return (1);
}
