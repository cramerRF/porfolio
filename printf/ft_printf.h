/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:55:30 by valonso           #+#    #+#             */
/*   Updated: 2021/11/17 19:07:05 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define MAXUINT 4294967295
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	pf_putchar(unsigned char c);
int	pf_putstr(char *s);
int	pf_puti(int n);
int	pf_putui(unsigned int n);
int	pf_putnbrbase(int n, char *base);
int	pf_putaddress(void *p);

#endif
