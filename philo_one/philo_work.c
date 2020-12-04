/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:28:49 by wupdegra          #+#    #+#             */
/*   Updated: 2020/12/04 17:24:05 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_check(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	while (!g_dead && (philo->curr_meals != philo->meal_times))
	{
		usleep(200);
		if (get_time_in_ms() - philo->last_meal_time >= (unsigned long long)philo->time_to_die)
		{
			if (philo->meal_times == -1)
				g_dead = true;
			if (g_dead)
				print_state(philo, "died");
			return (NULL);
		}
	}
	return (NULL);
}

int		philo_take_forks(t_philo *philo)
{
	// take left fork
	pthread_mutex_lock(philo->left_fork);
	if (g_dead) // check dead status after lock
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_state(philo, "has taken a fork");
	// take right fork
	pthread_mutex_lock(philo->right_fork);
	if (g_dead) // check dead status after lock
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_state(philo, "has taken a fork");
	return (1);
}

int		philo_eat(t_philo *philo)
{
	philo->last_meal_time = get_time_in_ms(); // set last meal time
	print_state(philo, "is eating");
	philo->curr_meals++;
	ft_usleep(philo->time_to_eat); // time to eat
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (g_dead) // check dead status after usleep
		return (0);
	return (1);
}

void	*philo_work(void *data)
{
	t_philo		*philo;
	pthread_t	checker;

	philo = (t_philo*)data;
	philo->last_meal_time = get_time_in_ms(); // set curr time
	pthread_create(&checker, NULL, philo_check, data); // thread checker
	if (philo->index % 2 == 0) // give forks through one
		ft_usleep(philo->time_to_sleep);
	while (!g_dead && (philo->curr_meals != philo->meal_times)) // if 5-th param not set, it value = -1
	{
		if (get_time_in_ms() - philo->start_time != 0) // think
			print_state(philo, "is thinking");
		if (!philo_take_forks(philo)) // take forks
			break ;
		if (!philo_eat(philo)) // eat
			break ;
		print_state(philo, "is sleeping"); // sleep
		ft_usleep(philo->time_to_sleep); // time to sleep
	}
	return (NULL);
}
