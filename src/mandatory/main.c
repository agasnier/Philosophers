/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/13 12:02:46 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	

	return (NULL);
}

int create_threads(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_create(&param->tab_philos[i].id, NULL, &routine, &param->tab_philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}


int	main(int argc, char *argv[])
{
	t_param	param;
	
	if (argc < 5 || argc > 6)
		return (1);

	if (init_struct(&param, argv))
	{
		printf("Error arguments\n");
		return (1);
	}

	if (create_tab_mutex(&param))
	{
		printf("Error create tab_mutex\n");
		return (1);
	}

	if (create_tab_philo(&param))
	{
		printf("Error create tab_philos\n");
		return (1);
	}

	if (create_threads(&param))
	{
		printf("Error create theads\n");
		return (1);
	}
	
	return (0);
}
