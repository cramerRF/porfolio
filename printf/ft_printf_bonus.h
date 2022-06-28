/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:02:30 by valonso           #+#    #+#             */
/*   Updated: 2021/11/23 15:15:26 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

int			ft_printf_aux_2(char s, va_list *ap);
int			ft_printf_aux_3(char s, void *var);
int			pf_sharp(char c, va_list *ap);
int			pf_plus(char c, va_list *ap);
int			pf_space(const char **s, va_list *ap);
int			pf_minus(const char **s, va_list *ap);
int			pf_zero(const char **s, va_list *ap);
int			pf_padding(const char **s, va_list *ap);
int			pf_strlen(char *s);
int			pf_len_in_base(long long int n, long long int len);
int			pf_len_var_aux(char c, va_list *ap);
int			pf_len_var(char c, va_list *ap);
long int	pf_atoi_foward(const char **s);
int			pf_dot(const char **s, va_list *ap);
int			pf_zero_aux(const char **s, va_list *ap, \
		int u_nbr, long int n_space);

#endif
