/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:45:57 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/19 21:39:08 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_start_philos(t_data *data)
{
	t_philo	philos[200];

	if (data->nb_philo == 1)
	{
		printf("%lld %d has taken a fork\n",
			p_get_time() - data->start_time, 1);
		usleep(1000 * data->time_to_die);
		printf("%lld %d died\n", p_get_time() - data->start_time, 1);
		return (1);
	}
	p_init_philos(data, philos);
	p_monitor_philos(data, philos);
	p_finalize_philos(data, philos);
	if (data->end_reason == FULL)
		printf("All meal eaten!\n");
	return (0);
}
