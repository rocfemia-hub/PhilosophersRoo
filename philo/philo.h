/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:01 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 23:24:53 by roo              ###   ########.fr       */
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
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				death_flag;
	int				philos_eaten;

}					t_aux;

typedef struct s_list
{
	struct s_list	*next;

	long			init;
	long			last_eat;
	pthread_t		thread;
	int				id;
	int				n_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			n_eats;
	long			eats_count;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;

	t_aux			*aux;
}					t_list;

//  DEATHS
int			is_this_death(t_list *philo);
int			is_other_death(t_list *philo);

// UTILS
long		ft_atol(const char *nptr);
t_list		*create_node(int id, char **argv, t_aux *aux);
long		get_time(long init);
void		ft_usleep(long milsec, t_list *philo);

// ROUTINE
void		*routine(void *arg);

#endif