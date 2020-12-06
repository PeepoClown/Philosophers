/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:51:29 by wupdegra          #+#    #+#             */
/*   Updated: 2020/12/06 17:39:39 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*philo_check(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	while (philo->curr_meals != philo->meal_times)
	{
		sem_wait(philo->status_sem);
		usleep(200);
		if (get_time_in_ms() - philo->last_meal_time >
			(unsigned long long)philo->time_to_die)
		{
			print_state(philo, "died");
			exit(1);
		}
		sem_post(philo->status_sem);
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_state(philo, "has taken a fork");
	philo->last_meal_time = get_time_in_ms();
	print_state(philo, "is eating");
	philo->curr_meals++;
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void		*philo_work(void *data)
{
	t_philo		*philo;
	pthread_t	checker;

	philo = (t_philo*)data;
	if (pthread_create(&checker, NULL, philo_check, data))
		return ((void*)ft_error("Can't create thread"));
	if (philo->index % 2 == 0)
		usleep(200);
	while (philo->curr_meals != philo->meal_times)
	{
		if (philo->curr_meals != 0)
			print_state(philo, "is thinking");
		philo_eat(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
	}
	exit(0);
}
