# include "philo.h"

int	valid_argument(char **argv)
{
	int i;
	int j;

	i = 1;
	if (argv[1][0] < '2' && !argv[1][1])
		return (printf("Need more philos\n"), 0);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Need numeric arguments\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int main (int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (valid_argument(argv) != 1)
		return (0);
	return (0);
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