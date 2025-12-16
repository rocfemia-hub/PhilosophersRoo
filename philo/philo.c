/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:12 by roo               #+#    #+#             */
/*   Updated: 2025/12/15 19:42:08 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_argument(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Need numeric arguments\n"), 0);
			j++;
		}
		if (ft_atol(argv[i]) < 1)
			return (printf("Invalid argument\n"), 0);
		i++;
	}
	return (1);
}

static void	free_all(t_list **list)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp_aux;
	int		aux;

	i = 0;
	tmp = *list;
	tmp_aux = tmp->next;
	aux = tmp->n_philos;
	pthread_mutex_destroy(&tmp->aux->death_mutex);
	pthread_mutex_destroy(&tmp->aux->print_mutex);
	while (aux > i)
	{
		tmp_aux = tmp->next;
		pthread_mutex_destroy(&tmp->l_fork);
		free(tmp);
		tmp = tmp_aux;
		i++;
	}
	return ;
}

static void	init_philos(int n_philos, char **argv, t_list **head, t_aux *aux)
{
	t_list	*node;
	t_list	*last;
	int		i;

	node = NULL;
	last = NULL;
	i = 0;
	while (i < n_philos)
	{
		node = create_node(i + 1, argv, aux);
		if (!*head)
			*head = node;
		else
		{
			last->r_fork = &node->l_fork;
			last->next = node;
		}
		last = node;
		i++;
	}
	last->r_fork = &(*head)->l_fork;
	last->next = *head;
}

static void	create_philos(t_list **list)
{
	int		i;
	t_list	*tmp;
	long	time_init;

	i = 0;
	tmp = *list;
	time_init = get_time(0);
	while (tmp->n_philos > i)
	{
		tmp->init = time_init;
		pthread_create(&tmp->thread, NULL, routine, tmp);
		tmp = tmp->next;
		i++;
	}
	while (0 < i--)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_list	*list;
	t_aux	aux;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (valid_argument(argv) != 1)
		return (0);
	list = NULL;
	aux.death_flag = 0;
	aux.philos_eaten = 0;
	pthread_mutex_init(&aux.death_mutex, NULL);
	pthread_mutex_init(&aux.print_mutex, NULL);
	init_philos(ft_atol(argv[1]), argv, &list, &aux);
	create_philos(&list);
	free_all(&list);
	return (0);
}
