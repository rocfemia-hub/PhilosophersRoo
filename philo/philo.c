/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:12 by roo               #+#    #+#             */
/*   Updated: 2025/12/09 00:43:43 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	get_time(long init)
{
	long	total_timer;
	struct	timeval tv;
	
	gettimeofday(&tv, NULL);
	total_timer = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (total_timer - init);
}

static int	valid_argument(char **argv)
{
	int i;
	int j;

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

int main (int argc, char **argv)
{
	t_list *list;
	//struct timeval timer;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (valid_argument(argv) != 1)
		return (0);
	list =	NULL;
	
	//gettimeofday(&timer, NULL);
	//initial_time.sec = timer.tv_sec * 1000;
	//initial_time.usec = timer.tv_usec / 1000;
	//printf("Tiempo antes: %ld\n", get_time(timer, initial_time));
	
	//ft_usleep(100000);
	//printf("Tiempo después: %ld\n", get_time(timer, initial_time));
	
	init_philos(ft_atol(argv[1]), argv, &list);
	create_philos(&list);
	
	return (printf("todo correcto :)\n"), 0);
}

void	create_philos(t_list **list)
{
	int i;
	long time_init;
	t_list *tmp;

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

//formato y rango
//pensar, comer y dormir (en ese orden)
//flag en estructura compartida para detectar muerte

//argv[0] =  ./philo
//argv[1] =  number_of_philosophers
//argv[2] =  time_to_die
//argv[3] =  time_to_eat
//argv[4] =  time_to_sleep
//argv[5] = [number_of_times_each_philosopher_must_eat]

//./philo "5 500 100 200"
// puede entrar así:./philo "5 500 100 200" y así: ./philo 5 500 100 200