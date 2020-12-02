#include "philo_one.h"

bool	ft_error(const char *error_msg)
{
	write(2, "\e[1;31m", 7);
	write(2, "Error : ", 8);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	return (false);
}
