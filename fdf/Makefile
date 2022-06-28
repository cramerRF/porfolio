# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valonso <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 19:29:47 by valonso           #+#    #+#              #
#    Updated: 2022/06/28 23:36:54 by valonso          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS_MACOS		= ./libs/libft/libft.a \
				  ./libs/minilibx_macos/libmlx.a

LIBS_LINUX		= ./libft.a \
				  ./libmlx.a \
				  ./libmlx_Linux.a

LFLAGS_MACOS	= -lmlx -framework OpenGL -framework AppKit -L.

LFLAGS_LINUX	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

GNL				= ./srcs/get_next_line/get_next_line.c \
				  ./srcs/get_next_line/get_next_line_utils.c

ALGEBRA			= ./srcs/algebra/alg_add.c

FDF_MY_PRO		= ./srcs/my_proyection/fdf_my_proyection.c

FDF_HOOKS		= ./srcs/fdf_hooks/fdf_hooks.c

FDF_INIT		= ./srcs/fdf_init/fdf_init.c

FDF_DRAW		= ./srcs/fdf_draw/fdf_colors.c \
				  ./srcs/fdf_draw/fdf_drawline_bresen.c \
				  ./srcs/fdf_draw/fdf_draw_utils.c \
				  ./srcs/fdf_draw/fdf_drawtri_solid.c

FDF_READ_MAP	= ./srcs/fdf_read_map/fdf_read_map.c \
				  ./srcs/fdf_read_map/fdf_read_map_checks.c \
				  ./srcs/fdf_read_map/fdf_read_map_aux.c

FDF_UTILS		= ./srcs/fdf_utils/fdf_utils_1.c

INC				= ./inc/fdf.h

SRCS			= ./srcs/fdf_main.c \
				  ${GNL} ${FDF_READ_MAP} ${FDF_UTILS} ${FDF_DRAW} ${FDF_HOOKS} ${FDF_INIT} ${ALGEBRA} ${FDF_MY_PRO}

OBJS			= ${SRCS:.c=.o}

CC				= cc

CFLAGS			= -D FDF_LINUX_COMPI #-Wall -Werror -Wextra

RM				= rm -f

NAME_MACOS		= fdf_macos

NAME_LINUX		= fdf_linux

.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME_MACOS}:	${INC} ${OBJS}
				make -C ./libs/libft
				make -C libs/minilibx_macos
				${CC} -o ${NAME_MACOS} ${LIBS_MACOS} ${OBJS} ${LFLAGS_MACOS}

${NAME_LINUX}:	${INC} ${OBJS}
				make -C ./libs/libft
				make -C libs/minilibx_linux
				${CC} ${OBJS} ${LFLAGS_LINUX} ./libft.a -o ${NAME_LINUX}

all:			${NAME_MACOS}

clean:
				${RM} ${OBJS}
				make clean -C ./libs/libft

fclean:			clean
				${RM} ${NAME_MACOS} ${NAME_LINUX}
				make fclean -C ./libs/libft
				make clean -C libs/minilibx_macos
				make clean -C libs/minilibx_linux

re:				fclean all

.PHONY:			all clean fclean re .c.o
