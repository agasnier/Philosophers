/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 12:31:03 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*tab_philos;
	t_param	param;
	
	if (argc < 5 || argc > 6) //gerer si moins de un philo
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
		return (1);
	}

	if (create_threads(&param, tab_philos))
	{
		printf("Error create theads\n");
		return (1);
	}
	
	join_threads(&param, tab_philos);
	
	return (0);
}
