/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:58:01 by wupdegra          #+#    #+#             */
/*   Updated: 2020/12/02 20:40:49 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_curr_mcs(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((int)tv.tv_usec);
}

void	init_config_helper(t_config *config)
{
	int		i;

	i = 0;
	while (i < config->philo_count)
		pthread_mutex_init(&(config->forks[i++]), NULL);
	i = 0;
	while (i < config->philo_count)
	{
		config->philos[i].index = i;
		config->philos[i].left_fork = (i != 0) ? &(config->forks[i - 1])
			: &(config->forks[config->philo_count - 1]);
		config->philos[i].right_fork = &(config->forks[i]);
		config->philos[i].time_to_die = config->time_to_die;
		config->philos[i].time_to_eat = config->time_to_eat;
		config->philos[i].time_to_sleep = config->time_to_sleep;
		config->philos[i].meals_count = config->meals_count;
		config->philos[i].meals = 0;
		config->philos[i].start_time = config->start_time;
		config->philos[i].last_meal_time = config->start_time;
		i++;
	}
}

int		init_config(t_config *config, char **args, int args_count)
{
	config->philo_count = ft_atoi(args[0]);
	config->time_to_die = ft_atoi(args[1]);
	config->time_to_eat = ft_atoi(args[2]);
	config->time_to_sleep = ft_atoi(args[3]);
	if (args_count > 4)
		config->meals_count = ft_atoi(args[4]);
	if (!(config->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
		* config->philo_count)))
		return (1);
	if (!(config->philos = (t_philo*)malloc(sizeof(t_philo)
		* config->philo_count)))
		return (1);
	if (!(config->threads = (pthread_t*)malloc(sizeof(pthread_t)
		* config->philo_count)))
		return (1);
	config->start_time = get_curr_mcs();
	init_config_helper(config);
	return (0);
}

void	*work(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	if (philo->index % 2 == 1)
		usleep(philo->time_to_sleep * 1000);
	while (1)//(check_meals(philo->meals))
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%d ms| %d : take left fork\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
		pthread_mutex_lock(philo->right_fork);
		printf("%d ms| %d : take right fork\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
		
		printf("%d ms| %d : start eating\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
		philo->last_meal_time = get_curr_mcs();
		if ((philo->last_meal_time - philo->start_time) / 1000 > philo->time_to_die)
		{
			printf("%d ms| %d : die(%d %d)\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index, philo->last_meal_time, philo->start_time);
			return (NULL);
		}
		usleep(philo->time_to_eat * 1000);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		printf("%d ms| %d : start sleeping\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
	
		usleep(philo->time_to_sleep * 1000);
		printf("%d ms| %d : start thinking\n", (philo->last_meal_time - philo->start_time) / 1000, philo->index);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_config	config;

	if (!validate_args(argv + 1, argc - 1))
		return (1);
	if (init_config(&config, argv + 1, argc - 1))
	{
		write(2, "\e[1;31m", 7);
		write(2, "Error : allocation error\n", 25);
		return (1);
	}



	error mgr need
	int i = 0;
	while (i < config.philo_count)
	{
		pthread_create(&(config.threads[i]), NULL, work,
			(void*)(&(config.philos[i])));
		i++;
	}
	i = 0;
	while (i < config.philo_count)
		pthread_join(config.threads[i], NULL);



	// free config & destroy mutexes
	return (0);
}
