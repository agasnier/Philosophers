/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:04:37 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/20 16:13:31 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(char *time_to_die)
{
	printf("%06ldms %4i %15s \n", ft_mini_atoi("0"), 1, "taken a fork");
	usleep(ft_mini_atoi(time_to_die) * 1000);
	printf("%06ldms %4i %15s \n", ft_mini_atoi(time_to_die), 1, "died");
}

static int	main_helper(t_param *param, t_philo **tab_philos)
{
	if (create_mutex(param))
	{
		printf("Error create tab_mutex\n");
		return (1);
	}
	if (create_tab_philo(param, tab_philos))
	{
		printf("Error create tab_philos\n");
		free_mutex_tab(param->mutex_forks, param->number_philo);
		free_mutex(param, NULL, 0, 3);
		return (1);
	}
	if (create_threads(param, *tab_philos))
	{
		printf("Error create theads\n");
		free_mutex_tab(param->mutex_forks, param->number_philo);
		free_mutex(param, tab_philos, param->number_philo, 7);
		return (1);
	}
	monitor(param, *tab_philos);
	join_threads(param, *tab_philos);
	free_mutex_tab(param->mutex_forks, param->number_philo);
	free_mutex(param, tab_philos, param->number_philo, 7);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*tab_philos;
	t_param	param;

	if (argc < 5 || argc > 6)
	{
		printf("./philo nb_philo time_to_die \
time_to_eat time_to_sleep [nb_meals]\n");
		return (1);
	}
	if (argv[1][0] == '1' && !argv[1][1])
	{
		one_philo(argv[2]);
		return (0);
	}
	if (init_struct(&param, argv))
	{
		printf("Error arguments\n");
		return (1);
	}
	if (main_helper(&param, &tab_philos))
		return (1);
	return (0);
}
