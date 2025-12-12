/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:01 by roo               #+#    #+#             */
/*   Updated: 2025/12/12 16:58:33 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_aux
{
    pthread_mutex_t death_mutex;
    int             death_flag;
	
}               	t_aux;

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

	t_aux        *aux;
}					t_list;

long		get_time(long init);
void		*routine(void *arg);

void		ft_usleep(long milsec, t_list *philo);
int			is_this_death(t_list *philo);
int			is_other_death(t_list *philo);

// LISTAS
long		ft_atol(const char *nptr);
void		init_philos(int n_philos, char **argv, t_list **head, t_aux *aux);
void		create_philos(t_list **list);

#endif