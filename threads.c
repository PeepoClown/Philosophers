#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

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

const int philo_count = 5;
const int sleep_time = 100;

typedef struct	s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
}				t_philo;

typedef struct	s_forks
{
	pthread_mutex_t mutexes[philo_count];
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
	for (int i = 0; i < philo_count; i++)
		pthread_mutex_init(&(forks->mutexes[i]), NULL);
}

pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;

void	*eat(void *data)
{
	t_philosophers *arg = (t_philosophers*)data;
	t_philo *philo = arg->philo;
	t_forks *forks = arg->forks;

	while (1)
	{
		printf("%d start eating\n", philo->id);

		pthread_mutex_lock(&entry_point);

		pthread_mutex_lock(&(forks->mutexes[philo->left_fork]));
		usleep(sleep_time * 1000);
		pthread_mutex_lock(&(forks->mutexes[philo->right_fork]));

		pthread_mutex_unlock(&entry_point);

		printf("%d philo sleep for %d ms\n", philo->id, sleep_time);

		pthread_mutex_unlock(&(forks->mutexes[philo->right_fork]));
		pthread_mutex_unlock(&(forks->mutexes[philo->left_fork]));

		printf("%d finish eating\n", philo->id);
	}

	return (NULL);
}

int		main(void)
{
	pthread_t threads[philo_count];

	t_philo philos[philo_count];
	t_forks forks;
	t_philosophers philosophers[philo_count];

	forks_init(&forks);
	for (int i = 0; i < philo_count; i++)
		philo_init(&(philos[i]), i + 1, i, (i + 1) % 5);
	for (int i = 0; i < philo_count; i++)
	{
		philosophers[i].philo = &(philos[i]);
		philosophers[i].forks = &forks;
	}

	for (int i = 0; i < philo_count; i++)
		pthread_create(&(threads[i]), NULL, eat, &(philosophers[i]));

	for (int i = 0; i < philo_count; i++)
		pthread_join(threads[i], NULL);

	return (0);
}
