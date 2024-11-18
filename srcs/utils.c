/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:30 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/14 21:06:48 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	p_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}

int	p_parse_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Usage: max_nb_philo, time_to_die, %s\n",
			"time_to_eat, time_to_sleep, [max eat]");
		return (1);
	}
	while (i < ac - 1)
	{
		if (ft_atoi(av[i + 1]) <= 0)
		{
			printf("Only positive numbers.\n");
			return (1);
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
	{
		printf("No more than 200 philosophers.\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	p_end_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->end_mutex));
	if (philo->data->have_to_end == 1)
	{
		pthread_mutex_unlock(&(philo->data->end_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->end_mutex));
	return (0);
}

int	p_sleep(t_data *data, int time)
{
	long long	start;

	start = p_get_time();
	while (p_get_time() - start <= time)
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->have_to_end == 1)
		{
			pthread_mutex_unlock(&(data->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(data->end_mutex));
		usleep(50);
	}
	return (0);
}
	