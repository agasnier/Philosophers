/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:08:33 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 14:36:36 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param
{
	long			number_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_must_eat;
	long			time_start;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	dead_lock;
	int				dead;
	pthread_mutex_t	write_lock;
}	t_param;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	long			last_eat;
	int				meal_eaten;
	pthread_mutex_t	meal_lock;
	t_param			*param;
}	t_philo;

//utils.c
int		is_dead_timer(t_philo *philo, long sleep);
long	get_time(void);
long	ft_mini_atoi(const char *argv);

//init.c
void	free_mutex_tab(pthread_mutex_t *tab, int i);
void	free_mutex(t_param *param, t_philo **philo, int number_philo, int mutex_o);
void	mutex_printf(t_philo *philo, long time, char *msg, int dead_lock);
int		create_mutex(t_param *param);
int		create_tab_philo(t_param *param, t_philo **tab_philos);
int		init_struct(t_param *param, char *argv[]);

//routine.c

void	*routine(void *arg);

//threads.c
void	monitor(t_param *param, t_philo *tab_philos);
int		create_threads(t_param *param, t_philo *tab_philos);
int		join_threads(t_param *param, t_philo *tab_philos);

#endif