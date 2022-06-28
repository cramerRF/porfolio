/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:12 by valonso           #+#    #+#             */
/*   Updated: 2021/11/16 21:46:19 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_aux(char s, va_list *ap)
{
	if (s == 'c')
		return (pf_putchar(va_arg(*ap, int)));
	if (s == 's')
		return (pf_putstr(va_arg(*ap, char *)));
	if (s == 'p')
		return (pf_putaddress(va_arg(*ap, void *)));
	if (s == 'd')
		return (pf_puti(va_arg(*ap, int)));
	if (s == 'i')
		return (pf_puti(va_arg(*ap, int)));
	if (s == 'u')
		return (pf_putui(va_arg(*ap, unsigned int)));
	if (s == 'x')
		return (pf_putnbrbase(va_arg(*ap, int), "0123456789abcdef"));
	if (s == 'X')
		return (pf_putnbrbase(va_arg(*ap, int), "0123456789ABCDEF"));
	if (s == '%')
		return (write(1, "\%", 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		sol;
	va_list	ap;

	sol = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s == '%')
			sol += ft_printf_aux(*(++s), &ap);
		else
			sol += write(1, s, 1);
		s++;
	}
	va_end(ap);
	return (sol);
}
