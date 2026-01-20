/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:13:47 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:32 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_timer(t_philo *philo, long sleep)
{
	long	time_start;

	time_start = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->param->dead_lock);
		if (philo->param->dead == 1)
		{
			pthread_mutex_unlock(&philo->param->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->param->dead_lock);
		if ((get_time() - time_start) >= sleep)
			break ;
		usleep(500);
	}
	return (0);
}

void	mutex_printf(t_philo *philo, long time, char *msg, int dead_lock)
{
	time -= philo->param->time_start;
	if (dead_lock)
		pthread_mutex_lock(&philo->param->dead_lock);
	if (philo->param->dead == 0)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("%ld %i %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->param->write_lock);
	}
	if (dead_lock)
		pthread_mutex_unlock(&philo->param->dead_lock);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_mini_atoi(const char *argv)
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
