/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:11 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/18 15:37:28 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define DEATH 1
# define FULL 2

typedef pthread_mutex_t	t_mutex;
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
	SATISFIED,
}	t_action;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				max_meal;
	long long		start_time;
	int				have_to_end;
	int				end_reason;
	t_mutex			log_mutex;
	t_mutex			end_mutex;
	t_mutex			forks[200];
}	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meal_remaining;
	long long		last_eaten;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_mutex			meal_mutex;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);

long long	p_get_time(void);

int			p_parse_args(int ac, char **av);

int			p_init_data(t_data *data, int ac, char **av);

int			p_init_mutexes(t_data *data);

int			p_destroy_mutexes(t_data *data);

int			p_start_philos(t_data *data);

int			p_check_dead(t_data *data, t_philo *philo, int *finished);

int			p_init_philos(t_data *data, t_philo *philos);

int			p_join_philos(t_data *data, t_philo *philos);

int			p_handle_single_philo(t_data *data);

void		*p_philo_action(void *arg);

int			p_eat_action(t_philo *philo);

int			p_track_philos( t_data *data, t_philo *philos);

int			p_log(t_philo *philo, t_action action);

int			p_end_check(t_philo *philo);

int			p_lock_fork_mutexes(t_philo *philo);

int			p_unlock_fork_mutexe(t_philo *philo);

int			p_sleep(t_data *data, int time);

#endif