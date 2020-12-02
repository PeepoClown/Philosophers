#include "philo_one.h"

int		ft_atoi(const char *str)
{
	int		result;
	int		sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str && *str >= 48 && *str <= 57)
		result = result * 10 + (*str++ - 48);
	return (result * sign);
}

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static bool	validate_number(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == '+')
		i++;
	if (i == ft_strlen(str))
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	if (i != ft_strlen(str))
		return (false);
	return (true);
}

static bool	validate_args_helper(char **args, int args_count)
{
	if (ft_atoi(args[0]) < 2)
	{
		write(2, "\e[1;31m", 7);
		write(2, "Error : Invalid count of philos\n", 32);
		return (false);
	}
	return (true);
}

bool		validate_args(char **args, int args_count)
{
	const char	*errors[5] = {
		"Error : Invalid count of philos\n", "Error : Invalid time to die\n",
		"Error : Invalid time to eat\n", "Error : Invalid time to sleep\n",
		"Error : Invalid eat times count\n"
	};
	int			i;

	if (args_count < 4 || args_count > 5)
	{
		write(2, "\e[1;31m", 7);
		write(2, "Error : Ivalid count of params.\n", 32);
		return (false);
	}
	i = 0;
	while (i < args_count)
	{
		if (!validate_number(args[i]))
		{
			write(2, "\e[1;31m", 7);
			write(2, errors[i], ft_strlen(errors[i]));
			return (false);
		}
		i++;
	}
	return (validate_args_helper(args, args_count));
}
