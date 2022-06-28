/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:12 by valonso           #+#    #+#             */
/*   Updated: 2021/11/23 14:53:27 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	pf_sharp(char c, va_list *ap)
{
	unsigned int	aux_sharp;

	if (c == 'x' || c == 'X')
		aux_sharp = va_arg(*ap, int);
	if (c == 'x' && aux_sharp)
		return (pf_putstr("0x") \
			+ pf_putnbrbase(aux_sharp, "0123456789abcdef"));
	if (c == 'X' && aux_sharp)
		return (pf_putstr("0X") \
			+ pf_putnbrbase(aux_sharp, "0123456789ABCDEF"));
	if ((c == 'x' || c == 'X') && !aux_sharp)
		return (pf_putchar('0'));
	return (ft_printf_aux_2(c, ap));
}

int	pf_plus(char c, va_list *ap)
{
	int	aux_plus;

	if (c == 'd' || c == 'i')
	{
		aux_plus = va_arg(*ap, int);
		if (aux_plus >= 0)
			return (pf_putchar('+') + pf_puti(aux_plus));
		return (pf_puti(aux_plus));
	}
	return (ft_printf_aux_2(c, ap));
}

int	pf_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long int	pf_atoi_foward(const char **s)
{
	long int	sol;

	sol = 0;
	while (**s <= '9' && **s >= '0')
		sol = sol * 10 + *(*s)++ - '0';
	return (sol);
}
