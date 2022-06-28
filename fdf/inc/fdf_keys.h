/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:59:04 by valonso           #+#    #+#             */
/*   Updated: 2022/03/09 19:16:42 by valonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_KEYS_H
# define FDF_KEYS_H

# ifdef	FDF_MACOS_COMPI
#  define FDF_ESC		53	// ESC

#  define FDF_FORWARD	13	// w
#  define FDF_BACKWARD	1	// s

#  define FDF_UP		15	// r
#  define FDF_DOWN		3	// f

#  define FDF_RIGHT		2	// d
#  define FDF_LEFT		0	// a

#  define FDF_ROT_RIGHT	37	// l
#  define FDF_ROT_LEFT	38	// j

#  define FDF_ROT_UP	34	// i
#  define FDF_ROT_DOWN	40	// k

#  define FDF_ZOOM_IN	257	// shift
#  define FDF_ZOOM_OUT	256	// control

#  define FDF_HELP		4	// h
#  define FDF_OPTIONS	5	// g

# endif

# ifdef	FDF_LINUX_COMPI

#  define FDF_ESC		'5'	// 5

#  define FDF_FORWARD	'w'	// w
#  define FDF_BACKWARD	's'	// s

#  define FDF_UP		'r'	// r
#  define FDF_DOWN		'f'	// f

#  define FDF_RIGHT		'd'	// d
#  define FDF_LEFT		'a'	// a

#  define FDF_ROT_RIGHT	'l'	// l
#  define FDF_ROT_LEFT	'j'	// j

#  define FDF_ROT_UP	'i'	// i
#  define FDF_ROT_DOWN	'k'	// k

#  define FDF_ZOOM_IN	'1'	// 1
#  define FDF_ZOOM_OUT	'2'	// 2

#  define FDF_HELP		'h'	// h
#  define FDF_OPTIONS	'g'	// g

# endif

#endif
