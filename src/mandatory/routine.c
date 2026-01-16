/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:29:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/16 15:16:14 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		mutex_printf(philo, get_time(), "taken a fork", 1);
		pthread_mutex_lock(philo->fork_left);
		mutex_printf(philo, get_time(), "taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		mutex_printf(philo, get_time(), "taken a fork", 1);
		pthread_mutex_lock(philo->fork_right);
		mutex_printf(philo, get_time(), "taken a fork", 1);
	}
}

static int	ft_eat(t_philo *philo)
{
	long	time;

	ft_eat_forks(philo);
	time = get_time();
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = time;
	pthread_mutex_unlock(&philo->meal_lock);
	mutex_printf(philo, time, "eating", 1);
	if (is_dead_timer(philo, philo->param->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	long	time;

	time = get_time();
	mutex_printf(philo, time, "sleeping", 1);
	if (is_dead_timer(philo, philo->param->time_to_sleep))
		return (1);
	return (0);
}

static int	ft_think(t_philo *philo)
{
	long	time;
	long	time_to_think;

	time = get_time();
	mutex_printf(philo, time, "thinking", 1);
	time_to_think = (philo->param->time_to_eat * 2) - philo->param->time_to_sleep;
	if (philo->id % 2 == 1)
	{
		if (time_to_think < 0)
			usleep(0);
		else
			usleep(time_to_think * 100);
	}	 	
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (ft_eat(philo))
			return (NULL);
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->meal_eaten == philo->param->number_must_eat)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meal_lock);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
