/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:22:10 by valonso           #+#    #+#             */
/*   Updated: 2022/03/22 18:23:51 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

t_point_ddd	alg_add_sp_ddd(t_point_ddd p1, t_point_ddd p2)
{
	t_point_ddd	res;

	res.x = p1.x + p2.x;
	res.y = p1.y + p2.y;
	res.z = p1.z + p2.z;
	return (res);
}

t_point_ddd	alg_sus_sp_ddd(t_point_ddd p1, t_point_ddd p2)
{
	t_point_ddd	res;

	res.x = p1.x - p2.x;
	res.y = p1.y - p2.y;
	res.z = p1.z - p2.z;
	return (res);
}

t_point_ddd	alg_fmul_sp_ddd(t_point_ddd p1, float k)
{
	t_point_ddd	res;
	
	res.x = p1.x * k;
	res.y = p1.y * k;
	res.z = p1.z * k;
	return (res);
}

float	alg_dot_pro_ddd(t_point_ddd p1, t_point_ddd p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

t_point_ddd	alg_norma_sp_ddd(t_point_ddd p)
{	
	t_point_ddd	res;
	float		mod;

	mod = sqrt(alg_dot_pro_ddd(p, p));
	res.x = p.x / mod;
	res.y = p.y / mod;
	res.z = p.z / mod;
	return (res);
}

t_point_ddd	alg_cross_product_ddd(t_point_ddd p1, t_point_ddd p2)
{
	t_point_ddd	sol;

	sol.x = p1.y * p2.z - p1.z * p2.y;
	sol.y = p1.z * p2.x - p1.x * p2.z;
	sol.z = p1.x * p2.y - p1.y * p2.x;
	sol = alg_norma_sp_ddd(sol);
	return (sol);
}

/*
	rodrigez formula
	v_rot = v * cos(angle) + (k x v) * sin(angle) + k (k dot v) (1 - cos(angle))
	*/

t_point_ddd alg_rodriguez_rot(t_point_ddd v, t_point_ddd axi, float angle)
{
	t_point_ddd	res;
	t_point_ddd	aux;
	float		aux_f;

	res = alg_fmul_sp_ddd(v, cos(angle));
	
	aux = alg_cross_product_ddd(axi, v);
	aux = alg_fmul_sp_ddd(aux, sin(angle));
	res = alg_add_sp_ddd(res, aux);
	
	aux_f = (1 - cos(angle)) * alg_dot_pro_ddd(axi, v);
	aux = alg_fmul_sp_ddd(axi, aux_f);
	res = alg_add_sp_ddd(res, aux);
	res = alg_norma_sp_ddd(res);
	return (res);
}
