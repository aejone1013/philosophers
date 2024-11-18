/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:54 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/14 21:07:23 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_lock_fork_mutexes(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	p_log(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	p_log(philo, FORK);
	return (0);
}

int	p_unlock_fork_mutexe(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
