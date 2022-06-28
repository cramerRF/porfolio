/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:15 by valonso           #+#    #+#             */
/*   Updated: 2021/11/16 20:46:16 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(unsigned char c)
{
	return (write(1, &c, 1));
}

int	pf_putstr(char *s)
{
	int	i;

	if (!s)
		return (pf_putstr("(null)"));
	i = -1;
	while (s[++i])
		pf_putchar(s[i]);
	return (i);
}

int	pf_putui(unsigned int n)
{
	if (n < 10)
		return (pf_putchar('0' + n));
	else
		return (pf_putui(n / 10) + pf_putchar('0' + n % 10));
}

int	pf_puti(int n)
{
	if (n < 0)
		return (pf_putchar('-') + pf_putui(-n));
	else
		return (pf_putui(n));
}
