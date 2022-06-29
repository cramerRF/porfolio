#ifndef GOD_H
# define GOD_H

#define TYPE_DATA	unsigned int

# include <unistd.h>
# include <time.h>
# include <stdlib.h>

typedef struct s_my_arr {
	TYPE_DATA	*arr;
	int	size;
} t_my_arr;

typedef struct s_my_aux {
	int		next;
	int		size;
	TYPE_DATA	value; 
} t_my_aux;


char	*ft_itoa(int n);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
#endif
