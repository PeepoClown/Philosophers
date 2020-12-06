/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:51:19 by wupdegra          #+#    #+#             */
/*   Updated: 2020/12/05 16:51:21 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool		ft_error(const char *error_msg)
{
	write(2, "\e[1;31m", 7);
	write(2, "Error : ", 8);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\e[0m", 4);
	write(2, "\n", 1);
	return (false);
}

static	int	ft_get_size(int n)
{
	int size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	size_t			sign;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	len = sign + ft_get_size(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len-- > sign)
	{
		str[len] = n % 10 + 48;
		n /= 10;
	}
	if (sign)
		str[len] = '-';
	return (str);
}

void		print_state(t_philo *philo, const char *msg)
{
	unsigned long long	curr_time;
	char				*buff;

	curr_time = get_time_in_ms() - philo->start_time;
	buff = (char*)malloc(sizeof(char) * (ft_strlen(ft_itoa(curr_time)) +
		ft_strlen(ft_itoa(philo->index)) + ft_strlen(msg) + 4));
	ft_strcpy(buff, ft_itoa(curr_time));
	ft_strcpy(buff + ft_strlen(ft_itoa(curr_time)), " ");
	ft_strcpy(buff + ft_strlen(ft_itoa(curr_time)) + 1, ft_itoa(philo->index));
	ft_strcpy(buff + ft_strlen(ft_itoa(curr_time)) + 1 +
		ft_strlen(ft_itoa(philo->index)), " ");
	ft_strcpy(buff + ft_strlen(ft_itoa(curr_time)) + 1 +
		ft_strlen(ft_itoa(philo->index)) + 1, (char*)msg);
	ft_strcpy(buff + ft_strlen(ft_itoa(curr_time)) + 1 +
		ft_strlen(ft_itoa(philo->index)) + 1 + ft_strlen(msg), "\n\0");
	write(1, buff, ft_strlen(buff));
	free(buff);
}
