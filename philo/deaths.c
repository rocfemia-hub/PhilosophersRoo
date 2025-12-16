/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:57:32 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 19:39:39 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_this_death(t_list *philo)
{
	pthread_mutex_lock(&philo->aux->death_mutex);
	if (philo->aux->death_flag == 1)
		return (pthread_mutex_unlock(&philo->aux->death_mutex), 1);
	if ((get_time(philo->init) - philo->last_eat) > philo->time_die)
	{
		philo->aux->death_flag = 1;
		pthread_mutex_unlock(&philo->aux->death_mutex);
		printf("%ld %d died\n", get_time(philo->init), philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->aux->death_mutex);
	return (0);
}

int	is_other_death(t_list *philo)
{
	pthread_mutex_lock(&philo->aux->death_mutex);
	if (philo->aux->death_flag == 1)
		return (pthread_mutex_unlock(&philo->aux->death_mutex), 1);
	return (pthread_mutex_unlock(&philo->aux->death_mutex), 0);
}
