/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 06:23:25 by valonso           #+#    #+#             */
/*   Updated: 2022/03/09 19:26:37 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

static void	fdf_drawline_bresen_i(int *all)
{
	if (all[1] >= 0)
		all[6] = 1;
	else
	{
		all[1] *= -1;
		all[6] = -1;
	}
	if (all[0] >= 0)
		all[5] = 1;
	else
	{
		all[0] *= -1;
		all[5] = -1;
	}
}

static void	fdf_drawline_bresen_r(int *all)
{
	if (all[0] >= all[1])
	{
		all[8] = 0;
		all[7] = all[5];
	}
	else
	{
		all[7] = 0;
		all[8] = all[6];
		fdf_swap_float((float *) all, (float *) (all + 1));
	}
}

static void	fdf_drawline_bresen_loop(t_fdf *fdf, \
		t_point_dd p1, t_point_dd p2, int *all)
{
	float	t;

	while ((int) p2.x != all[3] || (int) p2.y != all[4])
	{
		t = sqrt(((float) all[3] - p2.x) * ((float) all[3] - p2.x) \
				+ ((float)all[4] - p2.y) * ((float) all[4] - p2.y)) / (float) all[2];
		fdf_put_pixel(fdf, all[3], all[4], \
				fdf_parame_color(p1.color, p2.color, t));
		if (all[10] >= 0)
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

void	fdf_drawline_bresen(t_fdf *fdf, t_point_dd p1, t_point_dd p2)
{
	int	all[13];

	all[0] = (int) p2.x - (int) p1.x;
	all[1] = (int) p2.y - (int) p1.y;
	all[2] = sqrt(all[0] * all[0] + all[1] * all[1]);
	fdf_drawline_bresen_i(all);
	fdf_drawline_bresen_r(all);
	all[3] = p1.x;
	all[4] = p1.y;
	all[9] = 2.0f * all[1];
	all[10] = all[9] - all[0];
	all[11] = all[10] - all[0];
	fdf_drawline_bresen_loop(fdf, p1, p2, all);
}
