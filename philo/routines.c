/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 23:44:13 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(philo->r_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(&philo->l_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(&philo->l_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->eats_count++;
		philo->last_eat = get_time(philo->init);
		ft_usleep(philo->time_eat, philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(&philo->l_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(philo->r_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(&philo->l_fork), pthread_mutex_unlock(philo->r_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->eats_count++;
		philo->last_eat = get_time(philo->init);
		ft_usleep(philo->time_eat, philo);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	return (1);
}

static int	ft_sleep(t_list *philo)
{
	if (is_this_death(philo) || is_other_death(philo))
		return (0);
	printf("%ld %d is sleeping\n", get_time(philo->init), philo->id);
	ft_usleep(philo->time_sleep, philo);
	return (1);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	philo->last_eat = 0;
	if (philo->n_philos == 1 && one_philo(philo) == 0)
		return (NULL);
	while (1)
	{
		if (philo->n_eats != -1 && philo->eats_count == philo->n_eats)
			philo->aux->philos_eaten++;
		if (philo->n_eats != -1 && philo->aux->philos_eaten == philo->n_eats)
			break ;
		if (is_this_death(philo) || is_other_death(philo))
			return (NULL);
		/*if (philo->n_philos % 2 != 0)
			ft_usleep(200, philo);*/ //FUCK
		if (ft_eat(philo) == 0)
			return (NULL);
		if (ft_sleep(philo) == 0)
			return (NULL);
		if (is_this_death(philo) || is_other_death(philo))
			return (NULL);
		printf("%ld %d is thinking\n", get_time(philo->init), philo->id);
	}
	return (NULL);
}
