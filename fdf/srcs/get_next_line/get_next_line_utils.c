/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:15:18 by valonso           #+#    #+#             */
/*   Updated: 2022/03/02 16:57:53 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s)
		i++;
	return (i);
}

void	*gnl_memset(void *s, int c, int n)
{
	unsigned char	*aux;
	int				i;

	aux = s;
	i = -1;
	while (++i < n)
		*(aux + i) = c;
	return (s);
}

int	gnl_strlcpy(char *dst, char *src, int size)
{
	int	i;

	if (!size)
		return (gnl_strlen(src));
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = (char) src[i];
		i++;
	}
	dst[i] = '\0';
	return (gnl_strlen(src));
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*r;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	r = malloc(s1_len + s2_len + 1);
	if (!r)
		return (0);
	gnl_strlcpy(r, s1, s1_len + 1);
	gnl_strlcpy(r + s1_len, s2, s2_len + 1);
	free(s1);
	free(s2);
	return (r);
}
