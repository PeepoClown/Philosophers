/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:29:37 by wupdegra          #+#    #+#             */
/*   Updated: 2020/12/02 20:29:03 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

#include <stdio.h>

typedef struct	s_philo
{
	unsigned int	index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_count;
	unsigned int	meals;
	unsigned int	start_time;
	unsigned int	last_meal_time;
}				t_philo;

typedef struct	s_config
{
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_count;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*threads;
	unsigned int	start_time;
}				t_config;


bool	validate_args(char **args, int args_count);

int		ft_atoi(const char *str);

#endif
