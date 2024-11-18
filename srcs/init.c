/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:41 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/14 21:08:11 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_init_data(t_data *data, int ac, char **av)
{
	t_data	new;

	new.nb_philo = ft_atoi(av[1]);
	new.time_to_die = ft_atoi(av[2]);
	new.time_to_eat = ft_atoi(av[3]);
	new.time_to_sleep = ft_atoi(av[4]);
	new.start_time = p_get_time();
	new.have_to_end = 0;
	new.end_reason = 0;
	new.max_meal = -1;
	if (ac == 6)
		new.max_meal = ft_atoi(av[5]);
	*data = new;
	return (0);
}

int	p_init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->log_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->end_mutex), NULL) != 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (0);
}

int	p_destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(data->log_mutex)) != 0)
		return (0);
	if (pthread_mutex_destroy(&(data->end_mutex)) != 0)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			return (0);
		i++;
	}
	return (0);
}
