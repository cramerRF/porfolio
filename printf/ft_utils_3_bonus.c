/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:12 by valonso           #+#    #+#             */
/*   Updated: 2021/11/23 15:10:56 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

static int	pf_space_int_aux(int n)
{
	if (n < 0)
		return (pf_putchar('-') + pf_putui(-n));
	else
		return (pf_putchar(' ') + pf_putui(n));
}

int	pf_space(const char **s, va_list *ap)
{
	char	*str;

	(*s)++;
	if (**s <= '9' && **s >= '0')
		return (pf_padding(s, ap));
	if (**s == 's')
	{
		str = va_arg(*ap, char *);
		if (!str)
			return (write(1, " ", 1));
		return (pf_putstr(str));
	}
	if (**s == 'd' || **s == 'i')
		return (pf_space_int_aux(va_arg(*ap, int)));
	return (ft_printf_aux_2(**s, ap));
}

int	pf_zero_aux(const char **s, va_list *ap, \
		int u_nbr, long int n_space)
{
	int			sol;

	sol = 0;
	sol += pf_len_var(**s, ap);
	n_space -= sol;
	if (n_space > 0)
	{
		sol += n_space;
		while (n_space--)
			write (1, "0", 1);
	}
	if (**s == 'x')
		pf_putnbrbase(u_nbr, "0123456789abcdef");
	else if (**s == 'X')
		pf_putnbrbase(u_nbr, "0123456789ABCDEF");
	else
		pf_putui(u_nbr);
	return (sol);
}

int	pf_zero(const char **s, va_list *ap)
{
	long int	n_space;
	int			u_nbr;
	va_list		qa;

	va_copy(qa, *ap);
	u_nbr = va_arg(qa, int);
	n_space = pf_atoi_foward(s);
	if (u_nbr < 0 && (**s == 'd' || **s == 'i'))
	{
		write(1, "-", 1);
		u_nbr = -u_nbr;
	}
	va_end(qa);
	return (pf_zero_aux(s, ap, u_nbr, n_space));
}
