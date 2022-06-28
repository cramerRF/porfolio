/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 07:54:25 by valonso           #+#    #+#             */
/*   Updated: 2022/04/20 08:46:31 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

static t_cam	fdf_init_cam(void)
{
	t_cam	cam;

	cam.pos.x = 10;
	cam.pos.y = 0;
	cam.pos.z = 0;
	
	cam.nor.x = - sqrt(2.0f) / 2.0f;
	cam.nor.y = 1.0f / sqrt(6.0f);
	cam.nor.z = - sqrt(2.0f / 3.0f);
	
	cam.left.x = 0;
	cam.left.y = - sqrt(2.0f / 3.0f);
	cam.left.z = - sqrt(2.0f / 3.0f);
	
	cam.up.x = 0;
	cam.up.y = sqrt(2.0f / 3.0f);
	cam.up.z = - sqrt(2.0f / 3.0f);

	cam.nor.x = 1.0f;
	cam.nor.y = 0.0f;
	cam.nor.z = 0.0f;
	
	cam.focus = -10.0f;
	cam.zoom = 40.0f;
	return (cam);
}

static int	fdf_input_number(char *s)
{
	char	*aux;
	int		n;

	n = 0;
	while (n < 100 || n > 10000)
	{
		write(1, s, ft_strlen(s));
		aux = get_next_line(0);
		n = ft_atoi(aux);
		free(aux);
	}
	return (n);
}

static void	fdf_get_parameters(t_fdf *fdf)
{
	fdf->cam = fdf_init_cam();
	fdf->mlx = mlx_init();
	fdf->witdh = 1920;
	fdf->height = 1080;
	//fdf->witdh = fdf_input_number("Introduce witdh of screen:\n");
	//fdf->height = fdf_input_number("Introduce height of screen:\n");
	fdf->win = mlx_new_window(fdf->mlx, fdf->witdh, fdf->height, "FdF");
	fdf->img = mlx_new_image(fdf->mlx, fdf->witdh, fdf->height);
	fdf->addr = mlx_get_data_addr(fdf->img, \
			&fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
}

void	fdf_init_all(t_fdf *fdf)
{
	fdf_get_parameters(fdf);
	fdf_put_func_hook(fdf);
	mlx_hook(fdf->win, 2, 1L << 0, fdf_enable_hooks, fdf);
	mlx_loop_hook(fdf->mlx, fdf_render_next_frame_my_proyection, fdf);
	mlx_loop(fdf->mlx);
	fdf->k_xy = 4;
	fdf->k_z = 1;
}
