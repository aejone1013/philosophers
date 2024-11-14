/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:19 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/13 16:46:20 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_init_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(philos[i].meal_mutex), NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].data = data;
		philos[i].dead = 0;
		philos[i].id = i + 1;
		philos[i].last_eaten = philo_get_time();
		philos[i].meal_remaining = data->maximum_meal;
		philos[i].left_fork = &(data->forks[i]);
		philos[i].right_fork = &(data->forks[(i + 1) % data->nb_philo]);
		if (pthread_create(&(philos[i].thread_id),
				NULL, philo_action, &(philos[i])) != 0)
			return (1);
		i++;
	}
	return (1);
}

int	philo_join_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(philos[i].meal_mutex)))
			return (1);
		i++;
	}
	return (0);
}

int	philo_handle_single_philo(t_data *data)
{
	if (data->nb_philo == 1)
	{
		printf("%lld %d has taken a fork\n",
			philo_get_time() - data->start_time, 1);
		usleep(1000 * data->time_to_die);
		printf("%lld %d died\n", philo_get_time() - data->start_time, 1);
		return (1);
	}
	return (0);
}
