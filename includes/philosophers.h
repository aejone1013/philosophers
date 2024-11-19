/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:11 by jaoh              #+#    #+#             */
/*   Updated: 2024/11/19 22:57:04 by jaoh             ###   ########.fr       */
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
}	t_action;

typedef struct s_general
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
}	t_general;

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
	t_general			*general;
}	t_philo;

/* utils.c */
long long	p_get_time(void);

int	p_parse_args(int ac, char **av);

int	ft_atoi(const char *str);

int	p_check_end_condition(t_philo *philo);

int	p_sleep(t_general *general, int time);

/* start.c */
int	p_start_philos(t_general *general);

/* init.c */
int	p_init_data(t_general *general, int ac, char **av);

int	p_setup_mutexes(t_general *general);

int	p_cleanup_mutexes(t_general *general);

/* philos.c */
int	p_init_philos(t_general *general, t_philo *philos);

int	p_check_philo_state(t_general *general, t_philo *philo, int *finished);

int	p_monitor_philos( t_general *general, t_philo *philos);

int	p_finalize_philos(t_general *general, t_philo *philos);

/* actions.c */
int	p_sleep_action(t_philo *philo);

int	p_think_action(t_philo *philo);

int	p_eat_action(t_philo *philo);

void	*p_philo_action(void *arg);

/* forks.c */
int	p_grab_forks(t_philo *philo);

int	p_release_forks(t_philo *philo);

/* log.c */
int	p_print_log_message(long long start_t, int id, t_action action);

int	p_log_action(t_philo *philo, t_action action);

#endif