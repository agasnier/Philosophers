/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:29:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 16:44:01 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_printf(t_philo *philo, long time, char *msg)
{
	pthread_mutex_lock(&philo->param->dead_lock);
	if (philo->param->dead == 0)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("%ld %i %s \n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->param->write_lock);
	}
	pthread_mutex_unlock(&philo->param->dead_lock);
}

static int	ft_eat(t_philo *philo)
{
	long	time;

	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(philo->fork_left);
	mutex_printf(philo, get_time(), "taken a fork");
	pthread_mutex_lock(philo->fork_right);
	mutex_printf(philo, get_time(), "taken a fork");
	time = get_time();
	pthread_mutex_lock(&philo->param->dead_lock);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->param->dead_lock);
	mutex_printf(philo, time, "eating");
	if (is_dead_timer(philo, philo->param->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->param->write_lock);
	printf("%ld %i %s \n", time, philo->id, "sleeping");
	pthread_mutex_unlock(&philo->param->write_lock);
	if (is_dead_timer(philo, philo->param->time_to_sleep))
		return (1);
	return (0);
}

static int	ft_think(t_philo *philo)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->param->write_lock);
	printf("%ld %i %s \n", time, philo->id, "thinking");
	pthread_mutex_unlock(&philo->param->write_lock);
	if (is_dead_timer(philo, philo->param->time_to_sleep))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
