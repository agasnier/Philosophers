/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:30:38 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 12:30:58 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_create(&tab_philos[i].thread_id, NULL, &routine, &tab_philos[i]) != 0)
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