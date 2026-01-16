/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:30:38 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/16 12:10:08 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	long	time;
	
	time = get_time() - philo->last_eat;
	if (time > philo->param->time_to_die)
	{
		if (philo->param->number_must_eat != -1 && philo->meal_eaten >= philo->param->number_must_eat)
			return (0);
		return (1);
	}
	return (0);
}

void	monitor(t_param *param, t_philo *tab_philos)
{
	int		i;
	int		all_eaten;

	while (1)
	{
		i = -1;
		all_eaten = 0;
		while (++i < param->number_philo)
		{
			pthread_mutex_lock(&param->dead_lock);
			if (is_dead(&tab_philos[i]))
			{
				mutex_printf(&tab_philos[i], get_time(), "died", 0);
				param->dead = 1;
				pthread_mutex_unlock(&param->dead_lock);
				return ;
			}
			if (param->number_must_eat != -1 && tab_philos[i].meal_eaten >= param->number_must_eat)
				all_eaten++;
			pthread_mutex_unlock(&param->dead_lock);
		}
		if (param->number_must_eat != -1 && all_eaten == param->number_philo)
			return ;
		usleep(500);
	}
}

int	create_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_create(&tab_philos[i].thread_id, NULL,
				&routine, &tab_philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_join(tab_philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
