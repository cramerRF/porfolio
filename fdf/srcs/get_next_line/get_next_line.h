/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:01:20 by valonso           #+#    #+#             */
/*   Updated: 2022/03/04 03:45:47 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <unistd.h>

int		gnl_strlen(char *s);
void	*gnl_memset(void *s, int c, int n);
int		gnl_strlcpy(char *dst, char *src, int size);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
