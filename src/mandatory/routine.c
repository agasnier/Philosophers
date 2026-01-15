/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:29:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/15 12:54:50 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_left);
	mutex_printf(philo, get_time(), "taken a fork");
	if (philo->param->number_philo == 1 && is_dead_timer(philo, philo->param->time_to_die * 1.1))
		return (1);
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
	mutex_printf(philo, time, "sleeping");
	if (is_dead_timer(philo, philo->param->time_to_sleep))
		return (1);
	return (0);
}

static int	ft_think(t_philo *philo)
{
	long	time;

	time = get_time();
	mutex_printf(philo, time, "thinking");
	if (is_dead_timer(philo, 0))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		is_dead_timer(philo, philo->param->time_to_eat / 2);
	while (1)
	{
		if (ft_eat(philo))
			return (NULL);
		if (philo->meal_eaten == philo->param->number_must_eat)
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
