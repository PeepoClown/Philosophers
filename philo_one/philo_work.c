#include "philo_one.h"

t_state	get_state(t_philo *philo)
{
	t_state	state;

	state = philo->state;
	return (state);
}

void	set_state(t_philo *philo, t_state state)
{
	philo->state = state;
}

void	*philo_check(void *data)
{
	t_philo				*philo;
	unsigned long long	time_diff;

	philo = (t_philo*)data;
	while (1)
	{
		usleep(200);
		time_diff = get_time_in_ms() - philo->last_meal_time;
		if (time_diff >= (unsigned long long)philo->time_to_die)
		{
			if (philo->state != FED)
				philo->state = DEAD;
			if (philo->state == DEAD)
				print_state(philo, "died");
			return (NULL);
		}
	}
	return (NULL);
}

void	*philo_work(void *data)
{
	t_philo	*philo;
	pthread_t thread;

	philo = (t_philo*)data;
	if (philo->index - 1 % 2 == 1)
		usleep(philo->time_to_sleep);
	pthread_create(&thread, NULL, philo_check, data);
	philo->last_meal_time = get_time_in_ms();
	while (get_state(philo) != DEAD && philo->curr_meals != philo->meal_times)
	{
		pthread_mutex_lock(philo->left_fork);
		if (get_state(philo) == DEAD)
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		print_state(philo, "take left fork");
	
		pthread_mutex_lock(philo->right_fork);
		if (get_state(philo) == DEAD)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		print_state(philo, "take right fork");

		philo->last_meal_time = get_time_in_ms();
		print_state(philo, "start eating");
		usleep(philo->time_to_eat * 1000);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		if (get_state(philo) == DEAD)
			break ;

		print_state(philo, "start sleeping");
		usleep(philo->time_to_sleep * 1000);

		print_state(philo, "start thinking");
	}
	return (NULL);
}
