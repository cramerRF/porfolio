/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 06:23:25 by valonso           #+#    #+#             */
/*   Updated: 2022/03/04 08:15:40 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

static void	fdf_drawline_bresen_i(float *all)
{
	if (all[1] >= 0.0f)
		all[6] = 1.0f;
	else
	{
		all[1] *= -1.0f;
		all[6] = -1.0f;
	}
	if (all[0] >= 0.0f)
		all[5] = 1.0f;
	else
	{
		all[0] *= -1.0f;
		all[5] = -1.0f;
	}
}

static void	fdf_drawline_bresen_r(float *all)
{
	if (all[0] >= all[1])
	{
		all[8] = 0.0f;
		all[7] = all[5];
	}
	else
	{
		all[7] = 0.0f;
		all[8] = all[6];
		fdf_swap_float(all, all + 1);
	}
}

static void	fdf_drawtri_bresen_loop(t_fdf *fdf, \
		t_tri_dd tri, float *all)
{
	t_point_dd	aux;

	while (all[3] != tri.p2.x || all[4] != tri.p2.y)
	{
		aux.x = all[3];
		aux.y = all[4];
		all[12] = sqrt((all[3] - tri.p2.x) * (all[3] - tri.p2.x) \
				+ (all[4] - tri.p2.y) * (all[4] - tri.p2.y)) / all[2];
		aux.color = fdf_parame_color(tri.p1.color, tri.p2.color, all[12]);
		fdf_drawline_bresen(fdf, aux, tri.p3);
		if (all[10] >= 0.0f)
		{
			all[3] += all[5];
			all[4] += all[6];
			all[10] += all[11];
		}
		else
		{
			all[3] += all[7];
			all[4] += all[8];
			all[10] += all[9];
		}
	}	
}

void	fdf_drawtri_solid(t_fdf *fdf, t_tri_dd tri)
{
	float	all[13];

	all[0] = tri.p2.x - tri.p1.x;
	all[1] = tri.p2.y - tri.p1.y;
	all[2] = sqrt(all[0] * all[0] + all[1] * all[1]);
	fdf_drawline_bresen_i(all);
	fdf_drawline_bresen_r(all);
	all[3] = tri.p1.x;
	all[4] = tri.p1.y;
	all[9] = 2.0f * all[1];
	all[10] = all[9] - all[0];
	all[11] = all[10] - all[0];
	fdf_drawtri_bresen_loop(fdf, tri, all);
}
