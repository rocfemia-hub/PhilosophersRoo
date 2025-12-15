/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:20:46 by roo               #+#    #+#             */
/*   Updated: 2025/12/13 22:43:05 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	ft_eat(t_list *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if(is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (pthread_mutex_unlock(philo->right_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(&philo->left_fork);
		if(is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(&philo->left_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->eats_count++;
		philo->last_eat = get_time(philo->init);
		ft_usleep(philo->time_eat, philo); //usleep en microsegundos (1000 microsegundos = 1 milisegundo)
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		if(is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (pthread_mutex_unlock(&philo->left_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		pthread_mutex_lock(philo->right_fork);
		if (is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (pthread_mutex_unlock(&philo->left_fork), pthread_mutex_unlock(philo->right_fork), 0);
		printf("%ld %d has taken a fork\n", get_time(philo->init), philo->id);
		printf("%ld %d is eating\n", get_time(philo->init), philo->id);
		philo->eats_count++;
		philo->last_eat = get_time(philo->init);
		ft_usleep(philo->time_eat, philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (1);
}

static int	ft_sleep(t_list *philo)
{
	if(is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
		return (0);
	printf("%ld %d is sleeping\n", get_time(philo->init), philo->id);
	ft_usleep(philo->time_sleep, philo);
	return (1);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	philo->last_eat = 0; // esto se puede cambiar por get_time(philo->init)?
	/*if (!philo->next)
		funion d un filo*/ //no compruebes el rigth fork (lo ha dicho alguien muy listo)
	while (1)
	{
		if (philo->n_eats != -1 && philo->eats_count >= philo->n_eats) // esto no así :((((((, el resto tienen q seguir comiendo
			break;
		if (is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (NULL);
		/*if (philo->n_philos % 2 != 0)
			ft_usleep(200, philo);*/ //FUCK
		if (ft_eat(philo) == 0)
			return (NULL);
		if (ft_sleep(philo) == 0)
			return (NULL);
		if (is_this_death(philo) || is_other_death(philo)) // hay q poner esto por todas partes para evitar data races
			return (NULL);
		printf("%ld %d is thinking\n", get_time(philo->init), philo->id);
		}
	return (NULL);
}
