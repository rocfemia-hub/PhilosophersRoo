/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:01 by roo               #+#    #+#             */
/*   Updated: 2025/12/02 19:21:03 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list *next;

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

int			valid_argument(char **argv);

// LISTAS
long		ft_atol(const char *nptr);
t_list  	*create_node(int id, char **argv);
t_list		*last_node(t_list **list);
void		init_philos(int n_philos, char **argv, t_list **head);

#endif