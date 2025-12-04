/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:12 by roo               #+#    #+#             */
/*   Updated: 2025/12/04 20:44:12 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	time_controler(struct timeval timer, t_time time)
{
	long	total_timer;
	
	gettimeofday(&timer, NULL);
	total_timer = (timer.tv_sec * 1000 + timer.tv_usec / 1000);
	return (total_timer - (time.sec + time.usec));
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
	t_time initial_time;
	struct timeval timer;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (valid_argument(argv) != 1)
		return (0);
	list =	NULL;
	
	gettimeofday(&timer, NULL);
	initial_time.sec = timer.tv_sec * 1000;
	initial_time.usec = timer.tv_usec / 1000;
	printf("Tiempo antes: %ld\n", time_controler(timer, initial_time));
	
	usleep(100000);
	printf("Tiempo después: %ld\n", time_controler(timer, initial_time));
	
	init_philos(ft_atol(argv[1]), argv, &list);
	//pthread_create(&list->thread, NULL, ???(), &list);
	return (printf("todo correcto :)\n"), 0);
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