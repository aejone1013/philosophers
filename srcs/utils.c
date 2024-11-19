/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:30 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/19 22:35:01 by jaoh             ###   ########.fr       */
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

int	p_check_end_condition(t_philo *philo)
{
	pthread_mutex_lock(&(philo->general->end_mutex));
	if (philo->general->have_to_end == 1)
	{
		pthread_mutex_unlock(&(philo->general->end_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->general->end_mutex));
	return (0);
}

int	p_sleep(t_general *general, int time)
{
	long long	start;

	start = p_get_time();
	while (p_get_time() - start <= time)
	{
		pthread_mutex_lock(&(general->end_mutex));
		if (general->have_to_end == 1)
		{
			pthread_mutex_unlock(&(general->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(general->end_mutex));
		usleep(50);
	}
	return (0);
}
	