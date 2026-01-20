/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:52:58 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 16:25:00 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex_tab(pthread_mutex_t *tab, int i)
{
	if (tab)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&tab[i]);
		free(tab);
	}
}

void	free_mutex(t_param *param, t_philo **tab_philo,
		int number_philo, int mutex_o)
{
	if (mutex_o == 1 || mutex_o == 3 || mutex_o == 5 || mutex_o == 7)
		pthread_mutex_destroy(&param->dead_lock);
	if (mutex_o == 2 || mutex_o == 3 || mutex_o == 6 || mutex_o == 7)
		pthread_mutex_destroy(&param->write_lock);
	if (mutex_o == 4 || mutex_o == 5 || mutex_o == 6 || mutex_o == 7)
	{
		while (--number_philo >= 0)
			pthread_mutex_destroy(&(*tab_philo)[number_philo].meal_lock);
		if (tab_philo)
			free(*tab_philo);
	}
}

static int	create_mutex_helper(t_param *param, int i)
{
	if (pthread_mutex_init(&param->dead_lock, NULL) != 0)
	{
		free_mutex_tab(param->mutex_forks, i);
		return (1);
	}
	if (pthread_mutex_init(&param->write_lock, NULL) != 0)
	{
		free_mutex_tab(param->mutex_forks, i);
		free_mutex(param, NULL, 0, 1);
		return (1);
	}
	return (0);
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
			free_mutex_tab(param->mutex_forks, i);
			return (1);
		}
	}
	if (create_mutex_helper(param, i))
		return (1);
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
		(*tab_philos)[i].fork_right = &param->mutex_forks[(i + 1)
			% param->number_philo];
		(*tab_philos)[i].last_eat = 0;
		(*tab_philos)[i].meal_eaten = 0;
		if (pthread_mutex_init(&(*tab_philos)[i].meal_lock, NULL) != 0)
		{
			free_mutex(param, tab_philos, i, 4);
			return (1);
		}
		(*tab_philos)[i].param = param;
		i++;
	}
	return (0);
}
