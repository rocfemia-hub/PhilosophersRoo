/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/16 16:11:14 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_list *philo)
{
	while (1)
	{
		if (is_this_death(philo))
			return (0);
		pthread_mutex_lock(&philo->l_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_unlock(&philo->l_fork);
		ft_usleep(philo->time_die + 1, philo);
	}
	return (1);
}

static int	eat_first_r(t_list *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (is_this_death(philo) || is_other_death(philo))
		return (pthread_mutex_unlock(philo->r_fork), 0);
	printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
	pthread_mutex_lock(&philo->l_fork);
	if (is_this_death(philo) || is_other_death(philo))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(&philo->l_fork), 0);
	printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
	printf("%ld %d is eating\n", get_time(philo->init), philo->id);
	philo->eats_count++;
	philo->last_eat = get_time(philo->init);
	ft_usleep(philo->time_eat, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	return (1);
}

static int	ft_eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		if (eat_first_r(philo) == 0)
			return (0);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(&philo->l_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(philo->r_fork);
		if (is_this_death(philo) || is_other_death(philo))
			return (pthread_mutex_unlock(&philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), 0);
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
	pthread_mutex_lock(&philo->aux->print_mutex);
	if (is_this_death(philo) || is_other_death(philo))
		return (pthread_mutex_unlock(&philo->aux->print_mutex), 0);
	printf("%ld %d is sleeping\n", get_time(philo->init), philo->id);
	pthread_mutex_unlock(&philo->aux->print_mutex);
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
		if (is_this_death(philo) || is_other_death(philo) || !ft_eat(philo))
			return (NULL);
		if (philo->n_eats != -1 && philo->eats_count == philo->n_eats)
			philo->aux->philos_eaten++;
		if (philo->n_eats != -1 && philo->aux->philos_eaten == philo->n_philos)
			break ;
		if (ft_sleep(philo) == 0)
			return (NULL);
		if (is_this_death(philo) || is_other_death(philo))
			return (NULL);
		pthread_mutex_lock(&philo->aux->print_mutex);
		if (!is_this_death(philo) && !is_other_death(philo))
			printf("%ld %d is thinking\n", get_time(philo->init), philo->id);
		pthread_mutex_unlock(&philo->aux->print_mutex);
	}
	return (NULL);
}
