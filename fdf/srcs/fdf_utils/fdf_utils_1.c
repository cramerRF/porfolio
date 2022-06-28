/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:38:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/14 18:25:58 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	fdf_kill_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	fdf_count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	fdf_bases_to_int(char *s, char *base1, char *base2, int len_base)
{
	int	i;

	printf(".");
	if (*s == '\0')
		return (1);
	i = 0;
	while (i < len_base && *s != base1[i] && *s != base2[i])
		i++;
	return (i + len_base *  fdf_bases_to_int(s + 1, base1, base2, len_base));
}

void	fdf_swap_float(float *a, float *b)
{
	float	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
