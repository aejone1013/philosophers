/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:36 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/01 11:47:07 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_print_log_message(long long start_t, int id, t_action action)
{
	if (action == SLEEP)
		printf("%lld %d is sleeping\n", start_t, id);
	else if (action == EAT)
		printf("%lld %d is eating\n", start_t, id);
	else if (action == FORK)
		printf("%lld %d has taken a fork\n", start_t, id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", start_t, id);
	return (0);
}

int	p_log_action(t_philo *philo, t_action action)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&(philo->meal_mutex));
	if (philo->general->max_meal == 0)
	{
		pthread_mutex_unlock(&(philo->meal_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&(philo->general->log_mutex));
	if (action == DIED)
		printf("%lld %d died\n",
			p_get_time() - philo->general->start_time, philo->id);
	pthread_mutex_lock(&(philo->general->end_mutex));
	if (philo->general->have_to_end == 1)
		end = 1;
	pthread_mutex_unlock(&(philo->general->end_mutex));
	if (end != 1)
		p_print_log_message(p_get_time() - philo->general
			->start_time, philo->id, action);
	pthread_mutex_unlock(&(philo->general->log_mutex));
	return (0);
}
