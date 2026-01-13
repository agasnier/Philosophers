/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/13 11:21:50 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"





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
	
	return (0);
}
