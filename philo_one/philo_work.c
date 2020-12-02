#include "philo_one.h"

t_state	get_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->state_mutex);
	return (state);
}

void	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->state_mutex);
	philo->state = state;
	pthread_mutex_unlock(philo->state_mutex);
}

void	*philo_work(void *data)
{
	t_philo	*philo;
	pthread_t thread;

	philo = (t_philo*)data;
	if (philo->index % 2 == 1)
		usleep(philo->time_to_sleep);
	pthread_create(&thread, NULL, philo_check, data);
	philo->last_meal_time = get_time_in_ms();
	while (get_state(philo) != DEAD && philo->curr_meals != philo->meal_times)
	{
		// philo thinks
		pthread_mutex_lock(philo->left_fork);
		if (get_state(philo) == DEAD)
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
	}
	return (NULL);
}
