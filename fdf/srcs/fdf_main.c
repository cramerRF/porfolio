/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:35:35 by valonso           #+#    #+#             */
/*   Updated: 2022/03/14 13:07:21 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <time.h>

/*

	Exit codes:
		0 -> All good
		1 -> Bad file extension
		2 -> File not found
		3 -> File with bad content
  		
		10 -> Failed to malloc
 */

void	fdf_fatal_error(char *str, int exit_code)
{
	write(2, str, ft_strlen(str));
	system("leaks -q fdf_macos");
	exit(exit_code);
}

void    fdf_kill_fdf(t_fdf *fdf)
{
    int     i;
    
    i = 0;
    while (fdf->map[i] != NULL)
      free(fdf->map[i++]);
    free(fdf->map);
}

int	main(int argc, char **args)
{
	t_fdf	fdf;
    int     i;

	srand(time(NULL));
	if (argc != 2)
		fdf_fatal_error("To execute fdf_***** you only have to \
				pass one argument, a map with the extension .fdf\n", 0);
	fdf.map = fdf_read_map(args[1]);	
	fdf_init_all(&fdf);
    exit(99);
    printf("\nall good\nOK\n");
	fdf_kill_fdf(&fdf);
    system("leaks -q fdf_macos");
	return (0);
}
