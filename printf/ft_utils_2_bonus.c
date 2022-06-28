/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:12 by valonso           #+#    #+#             */
/*   Updated: 2021/11/23 08:53:32 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	pf_len_in_base(long long int n, long long int len)
{
	int				i;
	long long int	cont;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	cont = len;
	while (cont <= n)
	{
		cont *= len;
		i++;
	}
	return (i);
}

int	pf_len_var_aux(char c, va_list *ap)
{
	long int	nbr;

	nbr = va_arg(*ap, int);
	if (c == 'x' || c == 'X')
	{
		if (nbr < 0)
			nbr += 1 + MAXUINT;
		return (pf_len_in_base(nbr, 16));
	}
	return (pf_len_in_base(nbr, 10));
}

int	pf_len_var(char c, va_list *ap)
{
	char	*str;

	if (c == 'c' || c == '%')
		return (1);
	else if (c == 's')
	{
		str = va_arg(*ap, char *);
		if (!str)
			return (6);
		return (pf_strlen(str));
	}
	else if (c == 'p')
		return (2 + pf_len_in_base(va_arg(*ap, unsigned int), 16));
	else if (c == 'd' || c == 's' || c == 'x' || c == 'X' || c == 'i')
		return (pf_len_var_aux(c, ap));
	else if (c == 'u')
		return (pf_len_in_base(va_arg(*ap, unsigned int), 10));
	return (0);
}

int	pf_padding(const char **s, va_list *ap)
{
	long int	n_space;
	va_list		qa;
	int			sol;

	va_copy(qa, *ap);
	n_space = pf_atoi_foward(s);
	sol = 0;
	sol += pf_len_var(**s, ap);
	n_space -= sol;
	if (n_space > 0)
	{
		sol += n_space;
		while (n_space--)
			write (1, " ", 1);
	}
	ft_printf_aux_2(**s, &qa);
	va_end(qa);
	return (sol);
}

int	pf_minus(const char **s, va_list *ap)
{
	long int	n_space;
	long int	sol;

	(*s)++;
	n_space = pf_atoi_foward(s);
	sol = 0;
	sol += ft_printf_aux_2((char) **s, ap);
	n_space -= sol;
	if (n_space > 0)
	{
		sol += n_space;
		while (n_space--)
			write (1, " ", 1);
	}
	return (sol);
}
