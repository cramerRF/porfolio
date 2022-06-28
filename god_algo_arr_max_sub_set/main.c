#include <stdio.h>
#include "god.h"

t_my_arr	*create_new_arr(int size)
{
	t_my_arr	*arr;

	arr = malloc(sizeof(t_my_arr));
	if (!arr)
		return (NULL);
	arr->arr = malloc(sizeof(TYPE_DATA) * size);
	if (!arr->arr)
	{
		free(arr);
		return (NULL);
	}
	arr->size = size;
	return (arr);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	swap(TYPE_DATA	*a, TYPE_DATA *b)
{
	TYPE_DATA	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

t_my_arr	*create_rand_arr(int n)
{
	t_my_arr	*arr;
	int		i;

	if (n < 1)
		return (NULL);
	arr = malloc(sizeof(t_my_arr));
	if (!arr)
		return (NULL);
	arr->size = n;
	arr->arr = malloc(sizeof(TYPE_DATA) * n);
	if (!arr->arr)
	{
		free(arr);
		return (NULL);
	}
	i = -1;
	while (++i < n)
		arr->arr[i] = i + 1;
	while (++i < n * n)
		swap(&(arr->arr[rand() % n]), &(arr->arr[rand() % n]));
	return (arr);
}
/*
void	print_my_arr(t_my_arr *arr)
{
	int	i;
	char	*s;

	if (!arr)
		return ;
	write (1, "[", 1);
	i = 0;
	s = ft_itoa(arr->arr[i]);
	write(1, s, ft_strlen(s));
	free(s);
	while (++i < arr->size)
	{
		write (1, ", ", 2);
		s = ft_itoa(arr->arr[i]);
		write(1, s, ft_strlen(s));
		free(s);
	}
	write (1, "]\n", 2);

}
*/
void	kill_my_arr(t_my_arr *arr)
{
	if (!arr)
		return ;
	free(arr->arr);
	free(arr);
}


t_my_arr	*duplicate(t_my_arr *arr)	
{
	t_my_arr	*arr_x2;
	int		i;

	if (!arr)
		return (NULL);
	arr_x2 = malloc(sizeof(t_my_arr));
	if (!arr_x2)
		return (NULL);
	arr_x2->size = arr->size * 2;
	arr_x2->arr = malloc(arr_x2->size * sizeof(TYPE_DATA));
	if (!arr_x2->arr)
	{
		free(arr_x2);
		return (NULL);
	}
	i = -1;
	while (++i < arr->size)
		arr_x2->arr[i] = arr->arr[i];
	i--;
	while (++i < arr_x2->size)
		arr_x2->arr[i] = arr->arr[i - arr->size];
	return (arr_x2);
}

int	last_index(t_my_aux	*aux, int i)
{
	if (aux[i].next == -1)
		return (i);
	return (last_index(aux, aux[i].next));
}

t_my_aux	*get_aux_list_des(t_my_arr *arr_x2)
{
	t_my_aux	*aux;
	int		i;
	int		j;

	aux = malloc(sizeof(t_my_aux) * arr_x2->size);
	if (!aux)
	{
		kill_my_arr(arr_x2);
		return (NULL);
	}
	i = arr_x2->size - 1;
	aux[i].next = -1;
	aux[i].size = 1;
	aux[i].value = arr_x2->arr[i];
	while (--i != -1)
	{
		aux[i].value = arr_x2->arr[i];
		aux[i].next = -1;
		aux[i].size = 1;
		j = i;
		while (++j < arr_x2->size && last_index(aux, j) - i < arr_x2->size / 2 - 1)
		{
			if (aux[j].value < aux[i].value && aux[j].size + 1 > aux[i].size)
			{
				aux[i].size = aux[j].size + 1;
				aux[i].next = j;
			}
		}
	}
	return (aux);
}

t_my_aux	*get_aux_list_asc(t_my_arr *arr_x2)
{
	t_my_aux	*aux;
	int		i;
	int		j;

	aux = malloc(sizeof(t_my_aux) * arr_x2->size);
	if (!aux)
	{
		kill_my_arr(arr_x2);
		return (NULL);
	}
	i = arr_x2->size - 1;
	aux[i].next = -1;
	aux[i].size = 1;
	aux[i].value = arr_x2->arr[i];
	while (--i != -1)
	{
		aux[i].value = arr_x2->arr[i];
		aux[i].next = -1;
		aux[i].size = 1;
		j = i;
		while (++j < arr_x2->size && last_index(aux, j) - i < arr_x2->size / 2 - 1)
		{
			if (aux[j].value > aux[i].value && aux[j].size + 1 > aux[i].size)
			{
				aux[i].size = aux[j].size + 1;
				aux[i].next = j;
			}
		}
	}
	return (aux);
}

int		get_max(t_my_aux *aux, int size)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (++i < size)
	{
		if (aux[max].size < aux[i].size)
		       max = i;	
	}
	return (max);
}

t_my_arr	*get_sol(t_my_aux *aux, int size)
{
	int	max;
	int	i;
	int	j;
	t_my_arr	*sol;

	if (!aux)
		return (NULL);
	max = get_max(aux, size);
	sol = malloc(sizeof(t_my_arr));
	if (!sol)
		return (NULL);
	sol->arr = malloc(sizeof(TYPE_DATA) * aux[max].size);
	if (!sol->arr)
	{
		free(sol);
		return (NULL);
	}
	i = max;
	j = 0;
	while (aux[i].next != -1)
	{
		sol->arr[j++] = aux[i].value;
		i = aux[i].next;
	}
	sol->arr[j] = aux[i].value;
	sol->size = aux[max].size;
	return (sol);
}

t_my_arr	*get_max_des(t_my_arr *arr)
{
	t_my_arr	*arr_x2;
	t_my_arr	*sol;
	t_my_aux	*aux;
	
	arr_x2 = duplicate(arr);
	if (!arr_x2)
		return (NULL);
	aux = get_aux_list_des(arr_x2);
	if (!aux)
	{
		kill_my_arr(arr_x2);
		free(aux);
		return (NULL);
	}
	sol = get_sol(aux, arr_x2->size);
	kill_my_arr(arr_x2);
	free(aux);
	if (!sol)
		return (NULL);
	return (sol);
}

t_my_arr	*get_max_asc(t_my_arr *arr)
{
	t_my_arr	*arr_x2;
	t_my_arr	*sol;
	t_my_aux	*aux;
	
	arr_x2 = duplicate(arr);
	if (!arr_x2)
		return (NULL);
	aux = get_aux_list_asc(arr_x2);
	if (!aux)
	{
		kill_my_arr(arr_x2);
		free(aux);
		return (NULL);
	}
	sol = get_sol(aux, arr_x2->size);
	kill_my_arr(arr_x2);
	free(aux);
	if (!sol)
		return (NULL);
	return (sol);
}

int		is_in_arr(TYPE_DATA target, t_my_arr *arr)
{
	int	i;

	i = -1;
	while (++i < arr->size)
	{
		if (arr->arr[i] == target)
			return (1);
	}
	return (0);
}

t_my_arr	*sus_arr(t_my_arr *big, t_my_arr *small)
{
	int		i;
	int		j;
	t_my_arr	*sol;

	i = -1;
	j = 0;
	sol = create_new_arr(big->size - small->size);
	if (!sol)
		return (NULL);
	while (++i < big->size)
	{
		if (!is_in_arr(big->arr[i], small))
			sol->arr[j++] = big->arr[i];
	}
	return (sol);
}

int main(int argc, char **args)
{
	//char		*s;
	int		i;
	t_my_arr	*arr;
	t_my_arr	*sus;
	t_my_arr	*max_asc;
	t_my_arr	*max_des;

	if (argc != 2)
		return (0);
	srand(time(NULL));
	i = 0;
	arr = create_rand_arr(ft_atoi(args[1]));
	while (arr->size > 3)
	{
		i++;	
		//write (1, "\nStart\n", 7);
		printf("size %d\n", arr->size);
		//print_my_arr(arr);
		max_asc = get_max_asc(arr);
		max_des = get_max_des(arr);
		if (max_asc->size > max_des->size)
			sus = sus_arr(arr, max_asc);
		else	
			sus = sus_arr(arr, max_des);
		//write (1, "max_des", 7);
		//print_my_arr(max_des);
		//write (1, "max_asc", 7);
		//print_my_arr(max_asc);
		//write (1, "sus", 3);
		//print_my_arr(sus);
		kill_my_arr(arr);
		kill_my_arr(max_asc);
		kill_my_arr(max_des);
		arr = sus;	
	}
	//max_asc = get_max_asc(arr);
	//max_des = get_max_des(arr);
	//print_my_arr(max_asc);
	//print_my_arr(max_des);
	//write(1, "asc->size ", 10);
	//s = ft_itoa(max_asc->size);
	//write(1, s, ft_strlen(s));
	//free(s);
	//write(1, "des->size ", 10);
	//s = ft_itoa(max_des->size);
	//write(1, s, ft_strlen(s));
	//free(s);
	//write(1, "\n", 1);
	kill_my_arr(arr);
	//kill_my_arr(max_asc);
	//kill_my_arr(max_des);
	printf("Times %d\n", i);
	return (0);
}
