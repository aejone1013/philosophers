/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:45:57 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/14 21:06:15 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_start_philos(t_data *data)
{
	t_philo	philos[200];

	if (p_handle_single_philo(data))
		return (0);
	p_init_philos(data, philos);
	p_track_philos(data, philos);
	p_join_philos(data, philos);
	if (data->end_reason == FULL)
		printf("All meal eaten!\n");
	return (0);
}

int	p_check_dead(t_data *data, t_philo *philo, int *finished)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	if (p_get_time() - philo->last_eaten > data->time_to_die)
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->end_reason == 0)
			data->end_reason = DEATH;
		if (data->have_to_end != 1)
			philo->dead = 1;
		data->have_to_end = 1;
		pthread_mutex_unlock(&(data->end_mutex));
	}
	if (philo->meal_remaining == 0)
	{
		if (data->end_reason == 0)
			data->end_reason = FULL;
		*finished += 1;
	}
	pthread_mutex_unlock(&(philo->meal_mutex));
	return (0);
}

int	p_track_philos( t_data *data, t_philo *philos)
{
	int		i;
	int		j;
	int		finished;

	i = 0;
	while (data->have_to_end != 1)
	{
		j = 0;
		finished = 0;
		while (j < data->nb_philo)
		{
			pl_check_dead(data, &(philos[j++]), &finished);
		}
		if (finished == data->nb_philo)
		{
			pthread_mutex_lock(&(data->end_mutex));
			data->have_to_end = 1;
			pthread_mutex_unlock(&(data->end_mutex));
		}
		usleep(100);
		i++;
	}
	return (0);
}
