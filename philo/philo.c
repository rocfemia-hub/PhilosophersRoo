/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:12 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 19:42:08 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long init)
{
	struct timeval	tv;
	long			total_timer;

	gettimeofday(&tv, NULL);
	total_timer = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (total_timer - init);
}

static int	valid_argument(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Need numeric arguments\n"), 0);
			j++;
		}
		if (ft_atol(argv[i]) < 1)
			return (printf("Invalid argument\n"), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_list	*list;
	t_aux	aux;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (valid_argument(argv) != 1)
		return (0);
	list = NULL;
	aux.death_flag = 0;
	pthread_mutex_init(&aux.death_mutex, NULL);
	init_philos(ft_atol(argv[1]), argv, &list, &aux);
	create_philos(&list);
	free_all(&list);
	return (printf("todo correcto :)\n"), 0);
}

void	free_all(t_list **list)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp_aux;
	int		aux;

	i = 0;
	tmp = *list;
	tmp_aux = tmp->next;
	aux = tmp->n_philos;
	pthread_mutex_destroy(&tmp->aux->death_mutex);
	while (aux > i)
	{
		tmp_aux = tmp->next;
		pthread_mutex_destroy(&tmp->l_fork);
		free(tmp);
		tmp = tmp_aux;
		i++;
	}
	return ;
}

void	create_philos(t_list **list)
{
	int		i;
	t_list	*tmp;
	long	time_init;

	i = 0;
	tmp = *list;
	time_init = get_time(0);
	while (tmp->n_philos > i)
	{
		tmp->init = time_init;
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
		i++;
	}
	while (0 < i--)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	return ;
}
