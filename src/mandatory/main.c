/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/12 15:50:56 by algasnie         ###   ########.fr       */
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
	
	return (0);
}