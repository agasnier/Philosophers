/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/12 17:33:30 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_tab_philo(t_param *param)
{
	param->tab_philos = malloc(sizeof(int) * (param->number_philo + 1));
	if (!param->tab_philos)
		return (1);
		
	return (0);	
}

long	get_time(void)
{
	struct timeval tv;
		
	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
			
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

	if (create_tab_philo(&param))
	{
		printf("Error create tab_philos\n");
		return (1);
	}

	param.time_start = get_time();

	printf("%ld", param.time_start);
	
	return (0);
}