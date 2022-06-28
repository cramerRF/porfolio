/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:15 by valonso           #+#    #+#             */
/*   Updated: 2021/11/16 20:48:26 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_putib_r(unsigned long int n, char *base, int len)
{
	if (n < (unsigned long int) len)
		return (pf_putchar(base[n]));
	else
		return (pf_putib_r(n / len, base, len) + pf_putchar(base[n % len]));
}

static int	pf_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	pf_putnbrbase(int n, char *base)
{
	if (n < 0)
		return (pf_putib_r(MAXUINT + n + 1, base, pf_strlen(base)));
	else
		return (pf_putib_r(n, base, pf_strlen(base)));
}

int	pf_putaddress(void *p)
{
	return (pf_putstr("0x") + \
			pf_putib_r((unsigned long int) p, "0123456789abcdef", 16));
}
