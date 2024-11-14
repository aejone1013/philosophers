/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:49 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/13 17:09:58 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_sleep_action(t_philo *philo)
{
	philo_log(philo, SLEEP);
	ft_sleep(philo->data, philo->data->time_to_sleep);
	return (0);
}

int	pl_think_action(t_philo *philo)
{
	philo_log(philo, THINK);
	return (0);
}

int	philo_eat_action(t_philo *philo)
{
	philo_lock_fork_mutexes(philo);
	philo_log(philo, EAT);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_eaten = philo_get_time();
	pthread_mutex_unlock(&(philo->meal_mutex));
	ft_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->meal_remaining -= 1;
	pthread_mutex_unlock(&(philo->meal_mutex));
	philo_unlock_fork_mutexes(philo);
	return (0);
}

void	*philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->should_end != 1)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		if (philo_end_check(philo) == 1 || philo->meal_remaining == 0)
			break ;
		philo_eat_action(philo);
		if (philo_end_check(philo) == 1 || philo->meal_remaining == 0)
			break ;
		pl_sleep_action(philo);
		if (philo_end_check(philo) == 1 || philo->meal_remaining == 0)
			break ;
		pl_think_action(philo);
	}
	if (philo->dead == 1)
		philo_log(philo, DIED);
	return (NULL);
}
