/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:45:57 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/01 11:47:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_start_philos(t_general *general)
{
	t_philo	philos[200];

	if (general->nb_philo == 1)
	{
		printf("%lld %d has taken a fork\n",
			p_get_time() - general->start_time, 1);
		usleep(1000 * general->time_to_die);
		printf("%lld %d died\n", p_get_time() - general->start_time, 1);
		return (1);
	}
	p_init_philos(general, philos);
	p_monitor_philos(general, philos);
	p_finalize_philos(general, philos);
	if (general->end_reason == FULL)
		printf("All meal eaten!\n");
	return (0);
}
