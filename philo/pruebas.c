# include "philo.h"

typedef struct s_mutex
{
	int				result;
	pthread_mutex_t mutex;
}					t_mutex;

void	*routine_res(void *arg)
{
	t_mutex *strukt;

	strukt = arg;
	//usleep(? * 1000);
	pthread_mutex_lock(&strukt->mutex);
	strukt->result = strukt->result - 50;
	printf("Res-> %d\n", strukt->result);
	pthread_mutex_unlock(&strukt->mutex);
}

void	*routine_sum(void *arg)
{
	t_mutex *strukt;

	strukt = arg;
	pthread_mutex_lock(&strukt->mutex);
	strukt->result = strukt->result + 100;
	printf("Sum-> %d\n", strukt->result);
	pthread_mutex_unlock(&strukt->mutex);
}

int sumar(int n, int h)
{
	return n + h;
}

int restar(int n, int h)
{
	return n - h;
}

void operar_patatas(int (*operacion)(int, int), int arg, int arg2)
{
	printf("Operacion %d\n", operacion(arg, arg2));
}

int main (int argc, char **argv)
{
	pthread_t hilo_1;
	pthread_t hilo_2;
	t_mutex strukt;

	operar_patatas(&sumar, 10, 23);
	operar_patatas(&restar, 10, 23);
	strukt.result = 0;
	pthread_mutex_init(&strukt.mutex, NULL);
	pthread_mutex_init(&strukt.mutex, NULL);
	pthread_create(&hilo_1, NULL, routine_sum, &strukt);
	pthread_create(&hilo_2, NULL, routine_res, &strukt);
	pthread_join(hilo_1, NULL);
	pthread_join(hilo_2, NULL);
	printf("Result-> %d\n", strukt.result);
	return 0;
}