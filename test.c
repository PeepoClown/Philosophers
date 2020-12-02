#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED "\e[1;31m"
#define WHITE "\e[0m"

// static int	count = 0;
// pthread_mutex_t	mutex;

// void	*thread_func(void *data)
// {
// 	int		local = count;

// 	if (!strcmp((char*)data, "first") || !strcmp((char*)data, "third"))
// 		sleep(1);
// 	printf("thread_func working with data : %s\n", (char*)data);

// 	pthread_mutex_lock(&mutex);
// 	--local;
// 	count = local;
// 	printf("global value : %d\n", count);
// 	pthread_mutex_unlock(&mutex);

// 	pthread_exit(data);
// 	// return ("ret string");
// }


// int		main(void)
// {
// 	char			*data[] = { "first", "second", "third", "fourth", "fifth" };
// 	pthread_t		threads[5]; 
// 	pthread_attr_t	threads_attr[5]; 

// 	for (int i = 0; i < 5; i++)
// 		pthread_attr_init(&(threads_attr[i]));

// 	pthread_mutex_init(&mutex, NULL);
// 	for (int i = 0; i < 5; i++)
// 		pthread_create(&(threads[i]), &(threads_attr[i]), thread_func, (void*)data[i]);

// 	for (int i = 0; i < 5; i++)
// 	{
// 		void *storage = NULL;
// 		pthread_join(threads[i], &storage);
// 		printf("%d thread exit return : %s\n", i + 1, (char*)storage);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	// void	*thread1_exit_ret_value, *thread2_exit_ret_value;
// 	// printf("thread1 return : %d\n", ret_value1);
// 	// printf("thread1 exit return : %s\n", (char*)thread1_exit_ret_value);
// 	return (0);
// }

// int		main(void)
// {
// 	typedef struct timeval tv_t;
// 	tv_t tv;

// 	gettimeofday(&tv, NULL);
// 	int start = (int)tv.tv_usec;
// 	printf("started with : %d\n", start);

// 	usleep(200);

// 	gettimeofday(&tv, NULL);
// 	int end = (int)tv.tv_usec;
// 	printf("end with : %d\n", end);

// 	return (0);
// }

// const int philo_count = 5;
// const int sleep_time = 100;

// int		main(void)
// {
// 	pthread_t threads[philo_count];

// 	t_philo philos[philo_count];
// 	t_forks forks;
// 	t_philosophers philosophers[philo_count];

// 	forks_init(&forks);
// 	for (int i = 0; i < philo_count; i++)
// 		philo_init(&(philos[i]), i + 1, i, (i + 1) % 5);
// 	for (int i = 0; i < philo_count; i++)
// 	{
// 		philosophers[i].philo = &(philos[i]);
// 		philosophers[i].forks = &forks;
// 	}

// 	for (int i = 0; i < philo_count; i++)
// 		pthread_create(&(threads[i]), NULL, eat, &(philosophers[i]));

// 	for (int i = 0; i < philo_count; i++)
// 		pthread_join(threads[i], NULL);

// 	return (0);
// }

int philos_count = -1;
int time_to_die = -1;
int time_to_eat = -1;
int time_to_sleep = -1;
int eat_times_count = -1;
int start_time = 0;

typedef struct	s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
}				t_philo;

typedef struct	s_forks
{
	pthread_mutex_t *mutexes;
}				t_forks;

typedef struct	s_philosophers
{
	t_philo		*philo;
	t_forks		*forks;
}				t_philosophers;

void	philo_init(t_philo *philo, int id, int left, int right)
{
	philo->id = id;
	philo->left_fork = left;
	philo->right_fork = right;
}

void	forks_init(t_forks *forks)
{
	forks->mutexes = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * philos_count);
	for (int i = 0; i < philos_count; i++)
		pthread_mutex_init(&(forks->mutexes[i]), NULL);
}

pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;

void	*eat(void *data)
{
	t_philosophers *arg = (t_philosophers*)data;
	t_philo *philo = arg->philo;
	t_forks *forks = arg->forks;

	while (true)
	{
		printf("%d start eating\n", philo->id);

		pthread_mutex_lock(&entry_point);

		pthread_mutex_lock(&(forks->mutexes[philo->left_fork]));
		usleep(time_to_sleep * 1000);
		pthread_mutex_lock(&(forks->mutexes[philo->right_fork]));

		pthread_mutex_unlock(&entry_point);

		printf("%d philo sleep for %d ms\n", philo->id, time_to_sleep);

		pthread_mutex_unlock(&(forks->mutexes[philo->right_fork]));
		pthread_mutex_unlock(&(forks->mutexes[philo->left_fork]));

		printf("%d finish eating\n", philo->id);
	}

	return (NULL);
}


int		ft_atoi(const char *str)
{
	int		result;
	int		sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str && *str >= 48 && *str <= 57)
		result = result * 10 + (*str++ - 48);
	return (result * sign);
}

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

bool	validate_number(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == '+')
		i++;
	if (i == ft_strlen(str))
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	if (i != ft_strlen(str))
		return (false);
	return (true);
}

bool	validate_args_helper(char **args, int args_count)
{
	if (ft_atoi(args[0]) < 2)
	{
		write(2, RED, ft_strlen(RED));
		write(2, "Error : Invalid count of philos\n", 32);
		return (false);
	}
	return (true);
}

bool	validate_args(char **args, int args_count)
{
	const char	*errors[5] = {
		"Error : Invalid count of philos\n", "Error : Invalid time to die\n",
		"Error : Invalid time to eat\n", "Error : Invalid time to sleep\n",
		"Error : Invalid eat times count\n"
	};
	int			i;

	if (args_count < 4 || args_count > 5)
	{
		write(2, RED, ft_strlen(RED));
		write(2, "Error : Ivalid count of params.\n", 32);
		return (false);
	}
	i = 0;
	while (i < args_count)
	{
		if (!validate_number(args[i]))
		{
			write(2, RED, ft_strlen(RED));
			write(2, errors[i], ft_strlen(errors[i]));
			return (false);
		}
		i++;
	}
	return (validate_args_helper(args, args_count));
}

int		main(int argc, char **argv)
{
	if (!validate_args(argv + 1, argc - 1))
		return (EXIT_FAILURE);
	philos_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	eat_times_count = -1;
	if (argc == 6)
		eat_times_count = ft_atoi(argv[5]);
	printf("%d %d %d %d %d\n", philos_count, time_to_die, time_to_eat, time_to_sleep, eat_times_count);

	pthread_t threads[philos_count];
	t_philo philos[philos_count];
	t_forks forks;
	t_philosophers philosophers[philos_count];

	forks_init(&forks);
	for (int i = 0; i < philos_count; i++)
		philo_init(&(philos[i]), i + 1, i, (i + 1) % philos_count);
	for (int i = 0; i < philos_count; i++)
	{
		philosophers[i].philo = &(philos[i]);
		philosophers[i].forks = &forks;
	}
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	start_time = (int)tv.tv_usec;
	printf("%d\n", start_time);
	for (int i = 0; i < philos_count; i++)
		pthread_create(&(threads[i]), NULL, eat, &(philosophers[i]));

	for (int i = 0; i < philos_count; i++)
		pthread_join(threads[i], NULL);

	return (EXIT_SUCCESS);
}

// void	*work(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo*)data;
// 	if (philo->index % 2 == 1)
// 		usleep(philo->time_to_sleep * 1000);
// 	while (1)//(check_meals(philo->meals))
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		printf("%d ms| %d : take left fork\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
// 		pthread_mutex_lock(philo->right_fork);
// 		printf("%d ms| %d : take right fork\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
		
// 		printf("%d ms| %d : start eating\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
// 		philo->last_meal_time = get_curr_mcs();
// 		if ((philo->last_meal_time - philo->start_time) / 1000 > philo->time_to_die)
// 		{
// 			printf("%d ms| %d : die(%d %d)\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index, philo->last_meal_time, philo->start_time);
// 			return (NULL);
// 		}
// 		usleep(philo->time_to_eat * 1000);

// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);

// 		printf("%d ms| %d : start sleeping\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
	
// 		usleep(philo->time_to_sleep * 1000);
// 		printf("%d ms| %d : start thinking\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
// 	}
// 	return (NULL);
// }

