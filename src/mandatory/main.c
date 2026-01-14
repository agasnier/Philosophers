/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 16:30:09 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*tab_philos;
	t_param	param;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_struct(&param, argv))
	{
		printf("Error arguments\n");
		return (1);
	}
	if (create_mutex(&param))
	{
		printf("Error create tab_mutex\n");
		return (1);
	}
	if (create_tab_philo(&param, &tab_philos))
	{
		printf("Error create tab_philos\n");
		free_mutex(param.mutex_forks, param.number_philo,
			&param.dead_lock, &param.write_lock);
		return (1);
	}
	if (create_threads(&param, tab_philos))
	{
		printf("Error create theads\n");
		return (1);
	}
	monitor(&param, tab_philos);
	join_threads(&param, tab_philos);
	free_mutex(param.mutex_forks, param.number_philo,
		&param.dead_lock, &param.write_lock);
	free(tab_philos);
	return (0);
}
