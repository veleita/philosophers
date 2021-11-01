/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:17:55 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/01 19:07:30 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** pthread_create in line 38 opens a new thread that starts from function
** start_routine() in simulation.c and executes alongside the main thread
*/
t_philosopher	**get_philos(t_config *common)
{
	t_philosopher	**philos;
	struct timeval	start_time;
	int				i;

	philos = (t_philosopher **)malloc(sizeof(t_philosopher *) *
			common->number_of_philosophers);
	i = 0;
	while (i < common->number_of_philosophers)
		philos[i++] = (t_philosopher *)malloc(sizeof(t_philosopher));
	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		philos[i]->id = i + 1;
		philos[i]->meals = 0;
		philos[i]->common = common;
		philos[i]->timestamp = start_time;
		pthread_mutex_init(&(philos[i]->timelock), NULL);
		philos[i]->thread = malloc(sizeof(pthread_t *));
		pthread_create(philos[i]->thread, NULL, start_routine, philos[i]);
		i++;
	}
	return (philos);
}

pthread_mutex_t	**get_forks(int number_of_philos)
{
	pthread_mutex_t	**forks;
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t *) * number_of_philos);
	while (i < number_of_philos)
		forks[i++] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	i = 0;
	while (i < number_of_philos)
		pthread_mutex_init(forks[i++], NULL);
	return (forks);
}

t_config	parse(char **argv)
{
	t_config	common;

	common.number_of_philosophers = ft_atoi(argv[1]);
	common.time_to_die = ft_atoi(argv[2]);
	common.time_to_eat = ft_atoi(argv[3]);
	common.time_to_sleep = ft_atoi(argv[4]);
	return (common);	
}
