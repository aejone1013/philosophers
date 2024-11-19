/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:49 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/19 22:36:24 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_sleep_action(t_philo *philo)
{
	p_log_action(philo, SLEEP);
	p_sleep(philo->general, philo->general->time_to_sleep);
	return (0);
}

int	p_think_action(t_philo *philo)
{
	p_log_action(philo, THINK);
	return (0);
}

int	p_eat_action(t_philo *philo)
{
	p_grab_forks(philo);
	p_log_action(philo, EAT);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_eaten = p_get_time();
	pthread_mutex_unlock(&(philo->meal_mutex));
	p_sleep(philo->general, philo->general->time_to_eat);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->meal_remaining -= 1;
	pthread_mutex_unlock(&(philo->meal_mutex));
	p_release_forks(philo);
	return (0);
}

void	*p_philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->general->have_to_end != 1)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		if (p_check_end_condition(philo) == 1 || philo->meal_remaining == 0)
			break ;
		p_eat_action(philo);
		if (p_check_end_condition(philo) == 1 || philo->meal_remaining == 0)
			break ;
		p_sleep_action(philo);
		if (p_check_end_condition(philo) == 1 || philo->meal_remaining == 0)
			break ;
		p_think_action(philo);
	}
	if (philo->dead == 1)
		p_log_action(philo, DIED);
	return (NULL);
}
