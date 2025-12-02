/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/02 19:42:15 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
		printf("Eating\n");
		usleep(philo->time_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("Eating\n");
		usleep(philo->time_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void	*sleep(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
		printf("Sleeping\n");
		usleep(philo->time_sleep * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("Sleeping\n");
		usleep(philo->time_sleep * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}
