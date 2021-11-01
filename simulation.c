/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:11:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/01 19:11:05 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

void		*start_routine(void *arg)
{
	t_philosopher	*stats;

	stats = (t_philosopher *)arg;
	printf("I am philo %d!", stats->id);
	return ((void*)stats);
}

long int	get_time_from_last_meal(struct timeval t1, struct timeval t2)
{
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000)
		- (t2.tv_sec * 1000 + t2.tv_usec / 1000));
}

void	simulation(t_config *common, t_philosopher **philos,
		pthread_mutex_t **forks)
{
	int i;
	struct timeval	actual_time;
	(void)forks;

	while (true)
	{
		i = 0;
		while (i < common->number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i]->timelock);
			gettimeofday(&actual_time, NULL);
			if (get_time_from_last_meal(actual_time, philos[i]->timestamp)
					>= common->time_to_die)
				break;
			pthread_mutex_unlock(&philos[i++]->timelock);
		}
	}
}
