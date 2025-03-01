/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:19 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/01 11:47:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_init_philos(t_general *general, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < general->nb_philo)
	{
		if (pthread_mutex_init(&(philos[i].meal_mutex), NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < general->nb_philo)
	{
		philos[i].general = general;
		philos[i].dead = 0;
		philos[i].id = i + 1;
		philos[i].last_eaten = p_get_time();
		philos[i].meal_remaining = general->max_meal;
		philos[i].left_fork = &(general->forks[i]);
		philos[i].right_fork = &(general->forks[(i + 1) % general->nb_philo]);
		if (pthread_create(&(philos[i].thread_id),
				NULL, p_philo_action, &(philos[i])) != 0)
			return (1);
		i++;
	}
	return (1);
}

int	p_finalize_philos(t_general *general, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < general->nb_philo)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < general->nb_philo)
	{
		if (pthread_mutex_destroy(&(philos[i].meal_mutex)))
			return (1);
		i++;
	}
	return (0);
}

int	p_check_philo_state(t_general *general, t_philo *philo, int *finished)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	if (p_get_time() - philo->last_eaten > general->time_to_die)
	{
		pthread_mutex_lock(&(general->end_mutex));
		if (general->end_reason == 0)
			general->end_reason = DEATH;
		if (general->have_to_end != 1)
			philo->dead = 1;
		general->have_to_end = 1;
		pthread_mutex_unlock(&(general->end_mutex));
	}
	if (philo->meal_remaining == 0)
	{
		if (general->end_reason == 0)
			general->end_reason = FULL;
		*finished += 1;
	}
	pthread_mutex_unlock(&(philo->meal_mutex));
	return (0);
}

int	p_monitor_philos( t_general *general, t_philo *philos)
{
	int		i;
	int		j;
	int		finished;

	i = 0;
	while (!general->have_to_end)
	{
		j = 0;
		finished = 0;
		while (j < general->nb_philo)
		{
			p_check_philo_state(general, &(philos[j++]), &finished);
		}
		if (finished == general->nb_philo)
		{
			pthread_mutex_lock(&(general->end_mutex));
			general->have_to_end = 1;
			pthread_mutex_unlock(&(general->end_mutex));
		}
		usleep(500);
		i++;
	}
	return (0);
}
