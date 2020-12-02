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

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum		e_state
{
	LIVE = 0,
	DEAD,
	FED
}					t_state;

typedef struct		s_philo
{
	int					index;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_times;
	int					curr_meals;	
	unsigned long long	start_time;
	unsigned long long	last_meal_time;
	t_state				state;
	pthread_mutex_t		*state_mutex; // ?
}					t_philo;

typedef struct		s_params
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_times;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	unsigned long long	start_time;
}					t_params;

bool				validate_arguments(char **args, int args_count);
bool				ft_error(const char *error_msg);

void				*philo_work(void *data);

int					ft_atoi(const char *str);
int					ft_strlen(const char *str);
unsigned long long	get_time_in_ms(void);

#endif
