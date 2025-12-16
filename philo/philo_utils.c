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

long	ft_atol(const char *nptr)
{
	int		i;
	int		sig;
	long	result;

	i = 0;
	sig = 1;
	result = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sig = sig * -1;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sig);
}

t_list	*create_node(int id, char **argv, t_aux *aux)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->id = id;
	node->n_philos = ft_atol(argv[1]);
	node->time_die = ft_atol(argv[2]);
	node->time_eat = ft_atol(argv[3]);
	node->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		node->n_eats = ft_atol(argv[5]);
	else
		node->n_eats = -1;
	node->eats_count = 0;
	pthread_mutex_init(&node->l_fork, NULL);
	node->r_fork = NULL;
	node->next = NULL;
	node->aux = aux;
	return (node);
}

long	get_time(long init)
{
	struct timeval	tv;
	long			total_timer;

	gettimeofday(&tv, NULL);
	total_timer = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (total_timer - init);
}

void	ft_usleep(long milsec, t_list *philo)
{
	long	start;
	long	current;

	start = get_time(0);
	while (1)
	{
		current = get_time(0);
		if (is_this_death(philo) || is_other_death(philo))
			return ;
		if (current - start >= milsec)
			break ;
		usleep(10);
	}
}
