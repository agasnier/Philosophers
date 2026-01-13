/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:08:33 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/13 11:27:23 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
	int	id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t *fork_right;
	long	last_eat;
	
}	t_philo;

typedef struct	s_param
{
	long			number_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_must_eat;
	long			time_start;
	t_philo			*tab_philos;
	pthread_mutex_t	*mutex_forks;
	
}	t_param;

//utils.c
long	get_time(void);
int	ft_mini_atoi(const char *argv);

//init.c
int	create_tab_mutex(t_param *param);
int	create_tab_philo(t_param *param);
int	init_struct(t_param *param, char *argv[]);

#endif