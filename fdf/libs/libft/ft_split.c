/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:06:42 by valonso           #+#    #+#             */
/*   Updated: 2021/11/11 18:32:00 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**kill_split(char **split, size_t j)
{
	while (j)
		free(split[--j]);
	free(split);
	return (0);
}

static size_t	number_words(const char *s, char c)
{
	size_t	n_words;
	size_t	i;

	n_words = 0;
	i = 0;
	while (s[i++])
	{
		while (s[i] != c && s[i])
			i++;
		n_words++;
		while (s[i] == c && s[i])
			i++;
	}
	return (n_words);
}

static char	**split_aux(char const *s, char c, char **split)
{
	size_t	s_c;
	size_t	j;
	size_t	len_word;

	s_c = 0;
	j = 0;
	while (s[j])
	{
		len_word = 0;
		while (s[j + len_word] != c && s[j + len_word])
			len_word++;
		split[s_c] = malloc(len_word + 1);
		if (!split[s_c])
			return (kill_split(split, s_c));
		ft_strlcpy(split[s_c++], s + j, len_word + 1);
		j += len_word;
		while (s[j] == c && s[j])
			j++;
	}
	split[s_c] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	while (*s == c && *s)
		s++;
	split = malloc(8 * (number_words(s, c) + 1));
	if (!split)
		return (0);
	return (split_aux(s, c, split));
}
