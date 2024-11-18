/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:24 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/18 16:30:29 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (p_parse_args(ac, av) != 0)
		return (1);
	p_init_data(&data, ac, av);
	p_setup_mutexes(&data);
	p_start_philos(&data);
	p_cleanup_mutexes(&data);
}