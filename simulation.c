/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:11:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/03 13:44:03 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** PHILO THREAD
*/
void		eat_sleep_or_think(t_philosopher *stats)
{
	if (stats->time_to_die <= (stats->time_to_eat + stats->time_to_sleep))
	{
		take_forks(stats->forks);
		eat();
		sleep();
	}
	else
		think();
}

void		*start_routine(void *arg)
{
	t_philosopher	*stats;

	stats = (t_philosopher *)arg;
	while (stats->common->stop_simulation == false)
		eat_sleep_or_think();
}

/*
** MAIN THREAD
*/
long int	get_time_from_last_meal(struct timeval t1, struct timeval t2)
{
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000)
		- (t2.tv_sec * 1000 + t2.tv_usec / 1000));
}

void		check_stop_conditions(t_config *common, t_philosopher **philos)
{
	int i;
	struct timeval	actual_time;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i]->timelock);
		gettimeofday(&actual_time, NULL);
		if (get_time_from_last_meal(actual_time, philos[i]->last_meal_time)
				>= common->time_to_die)
		{
			common->stop_simulation = true;
			break;
		}
		pthread_mutex_unlock(&philos[i]->timelock);
		i++;
	}
}
