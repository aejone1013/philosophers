/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:54 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/18 16:36:43 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	p_log_action(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	p_log_action(philo, FORK);
	return (0);
}

int	p_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
