/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:24 by roo               #+#    #+#             */
/*   Updated: 2025/12/10 00:21:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sig;
	long	result;

	i = 0;
	sig = 1;
	result = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sig = sig * -1;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sig);
}

static t_list  *create_node(int id, char **argv, t_aux *aux)
{
    t_list  *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->id = id;
	node->n_philos = ft_atol(argv[1]);
	node->time_die = ft_atol(argv[2]);
	node->time_eat = ft_atol(argv[3]);
	node->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		node->n_eats = ft_atol(argv[5]);
	else
		node->n_eats = -1;
    pthread_mutex_init(&node->left_fork, NULL);
	node->right_fork = NULL;
    node->next = NULL;
	node->aux = aux;
    return (node);
}

/*static t_list	*last_node(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp && tmp->next)
	{
		if(tmp->id == tmp->n_philos)
			return (tmp);
		tmp = tmp->next;
	}
	return(tmp);
}*/

void	init_philos(int n_philos, char **argv, t_list **head, t_aux *aux)
{
	t_list *node;
	t_list *last;
	int i;

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
			last->right_fork = &node->left_fork;
			last->next = node;
		}
		last = node;
		i++;
	}
	last->right_fork = &(*head)->left_fork;
	last->next = *head;
}
