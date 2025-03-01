/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:24 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/01 11:47:07 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_general	general;

	if (p_parse_args(ac, av) != 0)
		return (1);
	p_init_data(&general, ac, av);
	p_setup_mutexes(&general);
	p_start_philos(&general);
	p_cleanup_mutexes(&general);
}
