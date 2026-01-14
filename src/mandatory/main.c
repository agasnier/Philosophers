/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/14 12:16:03 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_printf(t_philo *philo, long time, char *msg)
{
		
	pthread_mutex_lock(&philo->param->write_lock);
	printf("%ld %i %s \n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->param->write_lock);
}

void	ft_eat(t_philo *philo)
{
	long	time;

	if (philo->id % 2 == 0)
		usleep(1000);
	
	pthread_mutex_lock(philo->fork_left);
	mutex_printf(philo, get_time(), "taken a fork");
	pthread_mutex_lock(philo->fork_right);
	mutex_printf(philo, get_time(), "taken a fork");
	
	time = get_time();
	
	mutex_printf(philo, time, "eating");
	usleep(philo->param->time_to_eat * 1000); //faire une fonction plus precise ?
	philo->last_eat = time;
	
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	time = get_time();
	usleep(philo->param->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->param->write_lock);
	printf("%ld %i %s \n", time, philo->id, "sleeping");
	pthread_mutex_unlock(&philo->param->write_lock);
}

void	ft_think(t_philo *philo)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->param->write_lock);
	printf("%ld %i %s \n", time, philo->id, "thinking");
	pthread_mutex_unlock(&philo->param->write_lock);
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;


	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);

		//break if die of starvation or have all his meal
		
	}

	return (NULL);
}

int create_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_create(&tab_philos[i].thread_id, NULL, &routine, &tab_philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_param *param, t_philo *tab_philos)
{
	int	i;

	i = 0;
	while (i < param->number_philo)
	{
		if (pthread_join(tab_philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

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
