/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/09 01:20:24 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void ft_usleep(long milsec)
{
    long	start;
    long	current;
    
    start = get_time(0);
    while (1)
    {
        current = get_time(0);
        if (current - start >= milsec)
            break;
        usleep(10);
    }
}

static void	ft_eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(&philo->left_fork);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->last_eat = get_time(philo->init);
		ft_usleep(philo->time_eat); //usleep en microsegundos (1000 microsegundos = 1 milisegundo)
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
		ft_usleep(philo->time_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	ft_sleep(t_list *philo)
{
	printf("%ld %d is sleeping\n", get_time(philo->init), philo->id);
	ft_usleep(philo->time_sleep);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	philo->last_eat = 0;
	while (1)
	{
		if ((get_time(philo->init) - philo->last_eat) > philo->time_die) // hay q poner esto por todas partes para evitar data races
			break;
		printf("%ld %d is thinking\n", get_time(philo->init), philo->id);
		ft_eat(philo);
		ft_sleep(philo);
	}
	printf("%ld %d died\n", get_time(philo->init), philo->id);
	return (NULL);
}
