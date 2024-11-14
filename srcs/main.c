/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:24 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/13 16:46:25 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (philo_parse_args(ac, av) != 0)
		return (1);
	philo_init_data(&data, ac, av);
	philo_init_mutexes(&data);
	philo_start_philos(&data);
	philo_destroy_mutexes(&data);
}