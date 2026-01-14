/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:52:58 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 17:42:16 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mutex_forks, int i,
	pthread_mutex_t *dead_lock, pthread_mutex_t *write_lock)
{
	if (mutex_forks)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&mutex_forks[i]);
		free(mutex_forks);
	}
	if (dead_lock)
		pthread_mutex_destroy(dead_lock);
	if (write_lock)
		pthread_mutex_destroy(write_lock);
}

int	create_mutex(t_param *param)
{
	int	i;

	param->mutex_forks = malloc(sizeof(pthread_mutex_t) * param->number_philo);
	if (!param->mutex_forks)
		return (1);
	i = -1;
	while (++i < param->number_philo)
	{
		if (pthread_mutex_init(&param->mutex_forks[i], NULL) != 0)
		{
			free_mutex(param->mutex_forks, i, NULL, NULL);
			return (1);
		}
	}
	if (pthread_mutex_init(&param->dead_lock, NULL) != 0)
	{
		free_mutex(param->mutex_forks, i, NULL, NULL);
		return (1);
	}
	if (pthread_mutex_init(&param->write_lock, NULL) != 0)
	{
		free_mutex(param->mutex_forks, i, &param->dead_lock, NULL);
		return (1);
	}
	return (0);
}

int	create_tab_philo(t_param *param, t_philo **tab_philos)
{
	int	i;

	*tab_philos = malloc(sizeof(t_philo) * param->number_philo);
	if (!(*tab_philos))
		return (1);
	i = 0;
	while (i < param->number_philo)
	{
		(*tab_philos)[i].id = i + 1;
        (*tab_philos)[i].fork_left = &param->mutex_forks[i];
    	(*tab_philos)[i].fork_right = &param->mutex_forks[(i + 1) % param->number_philo];
		(*tab_philos)[i].last_eat = param->time_start;
		(*tab_philos)[i].meal_eaten = 0;
		(*tab_philos)[i].param = param;
		i++;
	}
	return (0);
}

int	init_struct(t_param *param, char *argv[])
{
	param->number_philo = ft_mini_atoi(argv[1]);
	if (param->number_philo == -1)
		return (1);
	param->time_to_die = ft_mini_atoi(argv[2]);
	if (param->time_to_die == -1)
		return (1);
	param->time_to_eat = ft_mini_atoi(argv[3]);
	if (param->time_to_die == -1)
		return (1);
	param->time_to_sleep = ft_mini_atoi(argv[4]);
	if (param->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		param->number_must_eat = ft_mini_atoi(argv[5]);
		if (param->number_must_eat == -1)
			return (1);
	}
	else
		param->number_must_eat = 0;
	param->time_start = get_time();
	param->dead = 0;
	return (0);
}
