/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/05 18:45:31 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void	*ft_eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(&philo->left_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->last_eat = get_time(philo->init);
		usleep(philo->time_eat * 1000); //usleep en microsegundos (1000 microsegundos = 1 milisegundo)
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->last_eat = get_time(philo->init);
		usleep(philo->time_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	*ft_sleep(t_list *philo)
{
	printf("%ld %d is sleeping\n", get_time(philo->init), philo->id);
	usleep(philo->time_sleep * 1000);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	while (1)
	{
		if (get_time(philo->last_eat) > philo->time_die) // hay q poner esto por todas partes para evitar data races
			break;
		printf("%ld %d is thinking\n", get_time(philo->init), philo->id);
		ft_eat(philo);
		ft_sleep(philo);
	}
	printf("%ld %d died\n", get_time(philo->init), philo->id);
}
