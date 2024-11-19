/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:41 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/19 22:32:28 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_init_data(t_general *general, int ac, char **av)
{
	t_general	new;

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
	*general = new;
	return (0);
}

int	p_setup_mutexes(t_general *general)
{
	int	i;

	if (pthread_mutex_init(&(general->log_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(general->end_mutex), NULL) != 0)
		return (0);
	i = 0;
	while (i < general->nb_philo)
	{
		if (pthread_mutex_init(&(general->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (0);
}

int	p_cleanup_mutexes(t_general *general)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(general->log_mutex)) != 0)
		return (0);
	if (pthread_mutex_destroy(&(general->end_mutex)) != 0)
		return (0);
	while (i < general->nb_philo)
	{
		if (pthread_mutex_destroy(&(general->forks[i])) != 0)
			return (0);
		i++;
	}
	return (0);
}
