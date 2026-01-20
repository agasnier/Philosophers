/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:21:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 16:25:09 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_param *param, char *argv[])
{
	param->number_philo = ft_mini_atoi(argv[1]);
	if (param->number_philo == -1)
		return (1);
	param->time_to_die = ft_mini_atoi(argv[2]);
	if (param->time_to_die == -1)
		return (1);
	param->time_to_eat = ft_mini_atoi(argv[3]);
	if (param->time_to_eat == -1)
		return (1);
	param->time_to_sleep = ft_mini_atoi(argv[4]);
	if (param->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		param->number_must_eat = ft_mini_atoi(argv[5]);
		if (param->number_must_eat == -1)
			return (1);
	}
	else
		param->number_must_eat = -1;
	param->dead = 0;
	return (0);
}
