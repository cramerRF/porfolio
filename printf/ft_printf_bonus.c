/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:58:05 by valonso           #+#    #+#             */
/*   Updated: 2021/11/23 08:51:09 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	ft_printf_aux_3(char s, void *var)
{
	if (s == 'c')
		return (pf_putchar(*((int *) var)));
	if (s == 's')
		return (pf_putstr((char *) var));
	if (s == 'p')
		return (pf_putaddress(var));
	if (s == 'd')
		return (pf_puti(*((int *) var)));
	if (s == 'i')
		return (pf_puti(*((int *) var)));
	if (s == 'u')
		return (pf_puti(*((unsigned int *) var)));
	if (s == 'x')
		return (pf_putnbrbase(*((int *) var), "0123456789abcdef"));
	if (s == 'X')
		return (pf_putnbrbase(*((int *) var), "0123456789ABCDEF"));
	if (s == '%')
		return (write(1, "\%", 1));
	return (0);
}

int	ft_printf_aux_2(char s, va_list *ap)
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

static	int	ft_printf_aux(const char **s, va_list *ap)
{
	(*s)++;
	if (**s == '#')
		return (pf_sharp((char) *++(*s), ap));
	if (**s == '+')
		return (pf_plus((char) *++(*s), ap));
	if (**s == '-')
		return (pf_minus(s, ap));
	if (**s > '0' && **s <= '9')
		return (pf_padding(s, ap));
	if (**s == ' ')
		return (pf_space(s, ap));
	if (**s == '0')
		return (pf_zero(s, ap));
	if (**s == '.')
		return (pf_dot(s, ap));
	return (ft_printf_aux_2((char) **s, ap));
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
			sol += ft_printf_aux(&s, &ap);
		else
			sol += write(1, s, 1);
		s++;
	}
	va_end(ap);
	return (sol);
}
