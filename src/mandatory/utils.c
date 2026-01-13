/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/13 09:53:54 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval tv;
		
	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
			
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
