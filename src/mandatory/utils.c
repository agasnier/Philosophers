/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/12 15:15:52 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mini_atoi(const char *argv)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	if (!argv)
		return (-1);
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		nbr *= 10;
		nbr += (argv[i] - '0');
		i++;
	}
	if (!argv[i])
		return (nbr);
	return (-1);
}

int	init_struct(t_param *param, char *argv[])
{
	param->number_philo = ft_mini_atoi(argv[1]);
	if (param->number_philo == -1)
		return (1);
	param->time_to_die = ft_mini_atoi(argv[2]);
	if (param->time_to_die == -1)
		return (1);
	param->time_to_eat = ft_mini_atoi(argv[3]);
	if (param->time_to_die == -1)
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
		param->number_must_eat = 0;

	printf("Param: %d ", param->number_philo);
	printf("%d ", param->time_to_die);
	printf("%d ", param->time_to_eat);
	printf("%d ", param->time_to_sleep);
	printf("%d\n", param->number_must_eat);

	return (0);
}