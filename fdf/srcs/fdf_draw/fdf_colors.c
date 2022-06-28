/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 06:23:15 by valonso           #+#    #+#             */
/*   Updated: 2022/03/11 18:03:13 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	fdf_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	fdf_get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	fdf_get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	fdf_get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	fdf_get_b(int trgb)
{
	return (trgb & 0xFF);
}
