#include "philo_one.h"

// void	*philo_check(void *data)
// {
// 	t_philo				*philo;
// 	unsigned long long	time_diff;

// 	philo = (t_philo*)data;
// 	while (!g_dead || (philo->meal_times != -1 && (philo->curr_meals != philo->meal_times)))
// 	{
// 		ft_usleep(300);
// 		time_diff = get_time_in_ms() - philo->last_meal_time;
// 		if (((time_diff > (unsigned long long)philo->time_to_die) && philo->meal_times == -1)
// 			|| ((time_diff > (unsigned long long)philo->time_to_die) && philo->meal_times != -1
// 			&& philo->curr_meals != philo->meal_times))
// 		{
// 			// if (philo->state != FED)
// 			// 	philo->state = DEAD;
// 			// if (philo->state == DEAD)
// 			// {
// 			// 	print_state(philo, "died");
// 			// 	g_dead = true;
// 			// }
// 			// return (NULL);
// 			pthread_mutex_unlock(philo->right_fork);
// 			pthread_mutex_unlock(philo->left_fork);
// 			print_state(philo, "died");
// 			g_dead = true;
// 		}
// 	}
// 	return (NULL);
// }

// void	*philo_work(void *data)
// {
// 	t_philo	*philo;
// 	pthread_t thread;

// 	philo = (t_philo*)data;
// 	if (philo->index % 2 == 0)
// 		ft_usleep(philo->time_to_sleep);
// 	pthread_create(&thread, NULL, philo_check, data);
// 	philo->start_time = get_time_in_ms();
// 	while (!g_dead && philo->curr_meals != philo->meal_times)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		if (g_dead) // get_state(philo) == DEAD
// 		{
// 			pthread_mutex_unlock(philo->left_fork);
// 			break ;
// 		}
// 		print_state(philo, "take left fork");
// 		ft_usleep(200);
	
// 		pthread_mutex_lock(philo->right_fork);
// 		if (g_dead) // get_state(philo) == DEAD
// 		{
// 			pthread_mutex_unlock(philo->right_fork);
// 			pthread_mutex_unlock(philo->left_fork);
// 			break ;
// 		}
// 		print_state(philo, "take right fork");
// 		ft_usleep(200);

// 		philo->last_meal_time = get_time_in_ms();
// 		print_state(philo, "start eating");
// 		philo->curr_meals++;
// 		ft_usleep(philo->time_to_eat * 1000);

// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);

// 		if (g_dead) // get_state(philo) == DEAD
// 			break ;

// 		print_state(philo, "start sleeping");
// 		ft_usleep(philo->time_to_sleep * 1000);

// 		if (g_dead) // get_state(philo) == DEAD
// 			break ;

// 		print_state(philo, "start thinking");
// 	}
// 	return (NULL);
// }

void	*philo_check(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	while (1)
	{
		usleep(200);
		if (get_time_in_ms() - philo->last_meal_time > (unsigned long long)philo->time_to_die)
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

void	*philo_work(void *data)
{
	t_philo		*philo;
	pthread_t	checker;

	philo = (t_philo*)data;

	philo->last_meal_time = get_time_in_ms();

	// checker thread
	pthread_create(&checker, NULL, philo_check, data);

	if (philo->index % 2 == 0)
		usleep(philo->time_to_sleep * 1000);

	while (!g_dead && (philo->curr_meals != philo->meal_times))
	{
		// take left fork
		pthread_mutex_lock(philo->left_fork);
		if (g_dead)
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		print_state(philo, "take left fork");

		// take right fork
		pthread_mutex_lock(philo->right_fork);
		if (g_dead)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		print_state(philo, "take right fork");

		// eat
		philo->last_meal_time = get_time_in_ms();
		print_state(philo, "start eating");
		philo->curr_meals++;
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// check dead after usleep
		if (g_dead)
			break ;

		// sleep
		print_state(philo, "start sleep");
		usleep(philo->time_to_sleep * 1000);

		// check dead after usleep
		if (g_dead)
			break ;

		// think
		print_state(philo, "start think");
	}

	return (NULL);
}
