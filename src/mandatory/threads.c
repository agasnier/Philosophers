/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:30:38 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/15 13:15:11 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




void	monitor(t_param *param, t_philo *tab_philos)
{
	int		i;
	long	between_meal;
	int		all_eaten;

	while (1)
	{
		i = 0;
		all_eaten = 0;
		while (i < param->number_philo)
		{
			if (tab_philos[i].meal_eaten == param->number_must_eat)
				all_eaten++;
			pthread_mutex_lock(&param->dead_lock);
			between_meal = get_time() - tab_philos[i].last_eat;
			pthread_mutex_unlock(&param->dead_lock);
			
			if (between_meal > param->time_to_die && tab_philos[i].meal_eaten < param->number_must_eat)
			{
				mutex_printf(&tab_philos[i], get_time(), "dead");
				pthread_mutex_lock(&param->dead_lock);
				param->dead = 1;
				pthread_mutex_unlock(&param->dead_lock);
				return ;
			}
			i++;
		}
		if (all_eaten == param->number_philo)
			return ;
		usleep(10);
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
