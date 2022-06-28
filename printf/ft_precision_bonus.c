/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:26:12 by valonso           #+#    #+#             */
/*   Updated: 2021/11/26 21:06:55 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"
#include <stdio.h>

int	pf_putstr_max(va_list *ap, long int max)
{
	long int	i;
	char		*s;

	i = -1;
	s = va_arg(*ap, char *);
	while (s[++i] && i < max)
		write(1, s + i, 1);
	return (i);
}

int	pf_dot(const char **s, va_list *ap)
{
	const char	*cpy;
	int			u_nbr;
	va_list		qa;
	long int	n_space;

	(*s)++;
	cpy = *s;
	va_copy(qa, *ap);
	u_nbr = va_arg(qa, int);
	va_end(qa);
	n_space = pf_atoi_foward(s);
	if (**s == 'p' && n_space == 0 && u_nbr == 0)
		return (pf_putstr("0x"));
	if (n_space == 0 && u_nbr == 0)
		return (0);
	if ((**s == 'i' ||**s == 'd') && (u_nbr < 0))
	{
		write(1, "-", 1);
		return (pf_zero_aux(s, ap, -u_nbr, n_space + 1));
	}
	if (**s == 'x' ||**s == 'X' ||**s == 'u' ||**s == 'i' ||**s == 'd')
		return (pf_zero(&cpy, ap));
	if (**s == 's')
		return (pf_putstr_max(ap, n_space));
	return (ft_printf_aux_2(**s, ap));
}
