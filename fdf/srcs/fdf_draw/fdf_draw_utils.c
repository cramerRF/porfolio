/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:35:35 by valonso           #+#    #+#             */
/*   Updated: 2022/03/07 19:30:40 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	fdf_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x > -1 && y > -1 && x < fdf->witdh && y < fdf->height)
	{
		dst = fdf->addr + (y * fdf->line_lenght \
				+ x * (fdf->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

int	fdf_parame_color(int c1, int c2, float t)
{
	int	trgb1[4];
	int	trgb2[4];
	int	trgb[4];

	trgb1[0] = fdf_get_t(c1);
	trgb1[1] = fdf_get_r(c1);
	trgb1[2] = fdf_get_g(c1);
	trgb1[3] = fdf_get_b(c1);
	trgb2[0] = fdf_get_t(c2);
	trgb2[1] = fdf_get_r(c2);
	trgb2[2] = fdf_get_g(c2);
	trgb2[3] = fdf_get_b(c2);
	trgb[0] = trgb1[0] * t + (1 - t) * trgb2[0];
	trgb[1] = trgb1[1] * t + (1 - t) * trgb2[1];
	trgb[2] = trgb1[2] * t + (1 - t) * trgb2[2];
	trgb[3] = trgb1[3] * t + (1 - t) * trgb2[3];
	return (fdf_create_trgb(trgb[0], trgb[1], trgb[2], trgb[3]));
}

void	fdf_drawtri(t_fdf *fdf, t_tri_dd tri)
{
	fdf_drawline_bresen(fdf, tri.p1, tri.p2);
	fdf_drawline_bresen(fdf, tri.p1, tri.p3);
	fdf_drawline_bresen(fdf, tri.p3, tri.p2);
}
