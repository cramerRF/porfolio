SRCS	= ft_printf.c ft_utils_1.c ft_utils_2.c
SRCSB	= ft_precision_bonus.c ft_printf_bonus.c ft_utils_1_bonus.c ft_utils_2_bonus.c ft_utils_3_bonus.c ft_utils_1.c ft_utils_2.c
HEAD	= ft_printf.h
HEADB	= ft_printf_bonus.h
OBJS	= ${SRCS:.c=.o}
OBJSB	= ${SRCSB:.c=.o}
CC	= cc
CFLAGS	= -Wall -Werror -Wextra
AR	= ar rc
NAME	= libftprintf.a
RM	= rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
		${AR} ${NAME} ${OBJS} && ranlib ${NAME}

clean:
		${RM} ${OBJS} ${OBJSB}

fclean:		clean
		${RM} ${NAME}

all:		${NAME}

re:		fclean all

bonus:		fclean ${OBJSB} ${HEADB}
		${AR} ${NAME} ${OBJSB} && ranlib ${NAME}

.PHONY:		all clean fclean re bonus
