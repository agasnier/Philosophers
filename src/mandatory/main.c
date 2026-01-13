/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/13 13:34:31 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	eat(t_philo *philo)
// {
	
// }

// void	sleep(t_philo *philo)
// {
	
// }

// void	think(t_philo *philo)
// {
	
// }

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;


	while (1)
	{
		pthread_mutex_lock();

		
		








		
	}

	return (NULL);
}

int create_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_create(&tab_philos[i].id, NULL, &routine, &tab_philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}


int	main(int argc, char *argv[])
{
	t_philo	tab_philos;
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

	if (create_tab_philo(&param, &tab_philos))
	{
		printf("Error create tab_philos\n");
		return (1);
	}

	if (create_threads(&param, &tab_philos))
	{
		printf("Error create theads\n");
		return (1);
	}
	
	return (0);
}
