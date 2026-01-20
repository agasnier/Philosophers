/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:30:38 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 16:14:10 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->meal_lock);
	if (philo->last_eat == 0)
		time = get_time() - philo->param->time_start;
	else
		time = get_time() - philo->last_eat;
	if (time > philo->param->time_to_die)
	{
		if (philo->param->number_must_eat != -1
			&& philo->meal_eaten >= philo->param->number_must_eat)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static void	all_meal_incr(t_param *param, t_philo *tab_philos,
			int *i, int *all_eaten)
{
	pthread_mutex_lock(&tab_philos[*i].meal_lock);
	if (param->number_must_eat != -1
		&& tab_philos[*i].meal_eaten >= param->number_must_eat)
		(*all_eaten)++;
	pthread_mutex_unlock(&tab_philos[*i].meal_lock);
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
			if (is_dead(&tab_philos[i]))
			{
				mutex_printf(&tab_philos[i], get_time(), "died", 0);
				pthread_mutex_lock(&param->dead_lock);
				param->dead = 1;
				pthread_mutex_unlock(&param->dead_lock);
				return ;
			}
			all_meal_incr(param, tab_philos, &i, &all_eaten);
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
	param->time_start = get_time();
	while (i < param->number_philo)
	{
		if (tab_philos[i].id % 2 == 1)
			if (pthread_create(&tab_philos[i].thread_id, NULL,
					&routine, &tab_philos[i]) != 0)
				return (1);
		i++;
	}
	usleep(2000);
	i = 0;
	while (i < param->number_philo)
	{
		if (tab_philos[i].id % 2 == 0)
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
