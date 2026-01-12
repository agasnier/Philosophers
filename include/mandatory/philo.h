/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:08:33 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/12 17:30:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int	fork;
}	t_philo;

typedef struct	s_param
{
	int		number_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_must_eat;
	long	time_start;
	t_philo	*tab_philos;
	
}	t_param;

//utils.c
int	ft_mini_atoi(const char *argv);
int	init_struct(t_param *param, char *argv[]);

#endif