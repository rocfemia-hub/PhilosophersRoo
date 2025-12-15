/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:11:51 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 19:46:18 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_list *philo)
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
