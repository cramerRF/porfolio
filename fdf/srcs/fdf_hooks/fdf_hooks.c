/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 06:49:08 by valonso           #+#    #+#             */
/*   Updated: 2022/03/24 03:10:04 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

#define DELTA_HORI_MOVE	2.0f
#define DELTA_ANGLE	0.05f
#define FDF_ZOOM	1.15f

t_point_ddd fdf_cross_product(t_point_ddd p1, t_point_ddd p2);
t_point_ddd alg_rodriguez_rot(t_point_ddd v, t_point_ddd axi, float angle);

static int	fdf_hook_nothing(void *fdf)
{
	return (0);
}

static int	fdf_close_win(void *fdf)
{
	mlx_destroy_image(((t_fdf *) fdf)->mlx, ((t_fdf *) fdf)->img);
	mlx_destroy_window(((t_fdf *) fdf)->mlx, ((t_fdf *) fdf)->win);
	system("leaks -q fdf_macos");
    exit(0);
	return (0);
}

int  fdf_print_cam(t_fdf *fdf)
{
	printf("Cam\n");
    printf("pos: %f, %f, %f\n", fdf->cam.pos.x, fdf->cam.pos.y, fdf->cam.pos.z);
    printf("nor: %f, %f, %f\n", fdf->cam.nor.x, fdf->cam.nor.y, fdf->cam.nor.z);
    printf("up: %f, %f, %f\n", fdf->cam.up.x, fdf->cam.up.y, fdf->cam.up.z);
    printf("left: %f, %f, %f\n", fdf->cam.left.x, fdf->cam.left.y, fdf->cam.left.z);
    printf("focus: %f\n", fdf->cam.focus);
    printf("zoom: %f\n", fdf->cam.zoom);
	return (0);
}

static t_point_ddd fdf_rotate_nvector(t_point_ddd p, float rads, int axi)
{
    t_point_ddd aux;
    
    if (!axi)
    {
        aux.x = p.x;
        aux.y = p.y * cos(rads) - p.z * sin(rads);
        aux.z = p.y * sin(rads) + p.z * cos(rads);
    }
    else if (axi == 1)
    {
        aux.x = p.x * cos(rads) + p.z * sin(rads);
        aux.y = p.y;
        aux.z = -p.x * sin(rads) + p.z * cos(rads);
    }
    else
    {
        aux.x = p.x * cos(rads) - p.y * sin(rads);
        aux.y = p.x * sin(rads) + p.y * cos(rads);
        aux.z = p.z;
    }
    return (aux);
}

static int  fdf_move_forward(void *fdf)
{
	t_point_ddd	aux;

	printf("Move forward\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.nor, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){1,0,0,0}, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_move_backward(void *fdf)
{
	t_point_ddd	aux;

	printf("Move backward\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.nor, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){1,0,0,0}, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_move_up(void *fdf)
{
	t_point_ddd	aux;

	printf("Move up\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.up, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){0,1,0,0}, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_move_down(void *fdf)
{
	t_point_ddd	aux;

	printf("Move down\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.up, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){0,1,0,0}, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_move_right(void *fdf)
{
	t_point_ddd	aux;

	printf("Move right\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.left, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){0,0,1,0}, DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_move_left(void *fdf)
{
	t_point_ddd	aux;

	printf("Move left\n");
    fdf_print_cam(fdf);
	aux = alg_fmul_sp_ddd(((t_fdf *) fdf)->cam.left, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	//aux = alg_fmul_sp_ddd((t_point_ddd){0,0,1,0}, -DELTA_HORI_MOVE / ((t_fdf *) fdf)->cam.zoom * 4 * 2);
	((t_fdf *) fdf)->cam.pos = alg_add_sp_ddd(((t_fdf *) fdf)->cam.pos, aux);
    return (0);
}

static int  fdf_rot_right(void *fdf)
{
	/*
	rodrigez formula
	v_rot = v * cos(angle) + (k x v) * sin(angle) + k (k dot v) (1 - cos(angle))
	*/
	/*
	t_point_ddd	aux1;
	t_point_ddd	axi;

	aux2 = ((t_fdf *fdf) fdf)->cam.nor;
	aux2 = fdf_

*/
	printf("Rotating right\n");
	/*
    ((t_fdf *)fdf)->cam.nor = fdf_rotate_nvector(((t_fdf *)fdf)->cam.nor, DELTA_ANGLE, 1);*/
    ((t_fdf *)fdf)->cam.nor = alg_rodriguez_rot(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up, DELTA_ANGLE);
    //((t_fdf *)fdf)->cam.left = alg_rodriguez_rot(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.up, DELTA_ANGLE);
	((t_fdf *) fdf)->cam.up = fdf_cross_product(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.nor);
	((t_fdf *)fdf)->cam.left = fdf_cross_product(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up);
	fdf_print_cam(fdf);
	return (0);
}

static int  fdf_rot_left(void *fdf)
{
	printf("Rotating left\n");
    //((t_fdf *)fdf)->cam.nor = fdf_rotate_nvector(((t_fdf *)fdf)->cam.nor, -DELTA_ANGLE, 1);
    ((t_fdf *)fdf)->cam.nor = alg_rodriguez_rot(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up, -DELTA_ANGLE);
    //((t_fdf *)fdf)->cam.left = alg_rodriguez_rot(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.up, -DELTA_ANGLE);
	((t_fdf *) fdf)->cam.up = fdf_cross_product(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.nor);
	((t_fdf *)fdf)->cam.left = fdf_cross_product(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up);
	fdf_print_cam(fdf);
    return (0);
}

static int  fdf_rot_up(void *fdf)
{
	printf("Rotating up\n");
    //((t_fdf *)fdf)->cam.nor = fdf_rotate_nvector(((t_fdf *)fdf)->cam.nor, DELTA_ANGLE, 2);
    ((t_fdf *)fdf)->cam.nor = alg_rodriguez_rot(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.left, DELTA_ANGLE);
    //((t_fdf *)fdf)->cam.up = alg_rodriguez_rot(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.left, DELTA_ANGLE);
	((t_fdf *) fdf)->cam.up = fdf_cross_product(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.nor);
	((t_fdf *)fdf)->cam.left = fdf_cross_product(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up);
    fdf_print_cam(fdf);
    return (0);
}

static int  fdf_rot_down(void *fdf)
{
	printf("Rotating down\n");
    //((t_fdf *)fdf)->cam.nor = fdf_rotate_nvector(((t_fdf *)fdf)->cam.nor, -DELTA_ANGLE, 2);
    ((t_fdf *)fdf)->cam.nor = alg_rodriguez_rot(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.left, -DELTA_ANGLE);
    //((t_fdf *)fdf)->cam.up = alg_rodriguez_rot(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.left, -DELTA_ANGLE);
	((t_fdf *) fdf)->cam.up = fdf_cross_product(((t_fdf *)fdf)->cam.left, ((t_fdf *)fdf)->cam.nor);
	((t_fdf *)fdf)->cam.left = fdf_cross_product(((t_fdf *)fdf)->cam.nor, ((t_fdf *)fdf)->cam.up);
    fdf_print_cam(fdf);
    return (0);
}

static int  fdf_zoom_out(void *fdf)
{
	printf("Zoom in\n");
	((t_fdf *)fdf)->cam.zoom /= FDF_ZOOM;
    return (0);
}

static int  fdf_zoom_in(void *fdf)
{
	printf("Zoom out\n");
	((t_fdf *)fdf)->cam.zoom *= FDF_ZOOM;
    return (0);
}

static int	fdf_help(void *fdf)
{
	printf("Help\n");
    return (0);
}

static int	fdf_options(void *fdf)
{
	printf("Options\n");
    return (0);
}

void	fdf_put_func_hook(t_fdf *fdf)
{
	int	i;

	i = -1;
	while (++i < 512)
		fdf->func_hook[i] = fdf_hook_nothing;
	fdf->func_hook[FDF_ESC] = fdf_close_win;

	fdf->func_hook[FDF_FORWARD] = fdf_move_forward;
	fdf->func_hook[FDF_BACKWARD] = fdf_move_backward;
	
	fdf->func_hook[FDF_UP] = fdf_move_up;
	fdf->func_hook[FDF_DOWN] = fdf_move_down;
	
	fdf->func_hook[FDF_RIGHT] = fdf_move_right;
	fdf->func_hook[FDF_LEFT] = fdf_move_left;
	
	fdf->func_hook[FDF_ROT_RIGHT] = fdf_rot_right;
	fdf->func_hook[FDF_ROT_LEFT] = fdf_rot_left;
	
	fdf->func_hook[FDF_ROT_UP] = fdf_rot_up;
	fdf->func_hook[FDF_ROT_DOWN] = fdf_rot_down;
	
	fdf->func_hook[FDF_ZOOM_IN] = fdf_zoom_in;
	fdf->func_hook[FDF_ZOOM_OUT] = fdf_zoom_out;

	fdf->func_hook[FDF_HELP] = fdf_help;
	fdf->func_hook[FDF_OPTIONS] = fdf_options;
}

int	fdf_enable_hooks(int keycode, t_fdf *fdf)
{
	printf("keycode -> %d\n", keycode);
	if (keycode > -1 && keycode < 512)
      fdf->func_hook[keycode](fdf);
	return (1);
}
