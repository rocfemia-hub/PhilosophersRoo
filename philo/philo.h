/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:01 by roo               #+#    #+#             */
/*   Updated: 2025/12/05 18:41:54 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_list
{
	struct s_list *next;

	long			init;
	long			last_eat;
	pthread_t		thread;
	int				id;
	int				n_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			n_eats;
	pthread_mutex_t left_fork;
	pthread_mutex_t *right_fork; //(next->left_fork)

}					t_list;

long		get_time(long init);
void		*routine(void *arg);

// LISTAS
long		ft_atol(const char *nptr);
void		init_philos(int n_philos, char **argv, t_list **head);
void		create_philos(t_list **list);

#endif