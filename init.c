/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:17:55 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/04 14:50:04 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** each philo starts its own thread from function start_routine() in
** simulation.c, this thread is executed alongside the main thread
*/
void			launch_philos(int number_of_philosophers, t_philosopher **philos)
{
	int i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_create(philos[i]->thread, NULL, start_routine, philos[i]);
		i++;
	}
}

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
		philos[i]->id = i;
		philos[i]->meals = 0;
		philos[i]->common = common;
		philos[i]->last_meal_time = start_time;
		pthread_mutex_init(&(philos[i]->timelock), NULL);
		philos[i]->thread = malloc(sizeof(pthread_t *));
		i++;
	}
	return (philos);
}

t_fork			*get_forks(int number_of_philos)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * number_of_philos);
	while (i < number_of_philos)
	{
		forks[i].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i].mutex, NULL);
		forks[i++].state = AVAIABLE;
	}
	return (forks);
}

t_config	get_common(char **argv)
{
	t_config	common;

	common.number_of_philosophers = ft_atoi(argv[1]);
	common.time_to_die = ft_atoi(argv[2]);
	common.time_to_eat = ft_atoi(argv[3]);
	common.time_to_sleep = ft_atoi(argv[4]);
	common.forks = get_forks(common.number_of_philosophers);
	common.stop_simulation = false;
	gettimeofday(&common.start_time, NULL);
	return (common);	
}
