#include "philo_one.h"

bool	ft_error(const char *error_msg)
{
	write(2, "\e[1;31m", 7);
	write(2, "Error : ", 8);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	return (false);
}

void	print_number(unsigned long long num)
{
	char	curr;

	if (num < 10)
	{
		curr = num + 48;
		write(1, &curr, 1);
	}
	else
	{
		print_number(num / 10);
		print_number(num % 10);
	}
}

void	print_state(t_philo *philo, const char *msg)
{
	unsigned long long	curr_time;

	pthread_mutex_lock(philo->output_mutex);
	write(1, "[", 1);
	curr_time = get_time_in_ms() - philo->start_time;
	print_number(curr_time);
	write(1, " ms] ", 5);
	print_number(philo->index);
	write(1, " : ", 3);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->output_mutex);
}
