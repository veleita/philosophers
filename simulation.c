/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:11:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/04 15:58:49 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** PHILO THREAD
*/
static void	eat_sleep_or_think(t_philosopher *stats)
{
	long int	time_left;
	int			time_to_digest;

	time_left = stats->common->time_to_die -
		time_struct_to_int(stats->last_meal_time);
	time_to_digest = stats->common->time_to_eat + stats->common->time_to_sleep;
	if (time_left - time_to_digest <= 0)
	{
		take_forks(stats->id, stats->common->number_of_philosophers - 1,
				stats->common);
		philo_eat(stats);
		philo_sleep(stats->id, stats->common);
		printer(THINK, stats->id, stats->common);
	}
}

void	*start_routine(void *arg)
{
	t_philosopher	*stats;

	stats = (t_philosopher *)arg;
	while (stats->common->stop_simulation == false)
		eat_sleep_or_think(arg);
	return (NULL);
}

/*
** MAIN THREAD
*/
void	check_stop_conditions(t_config *common, t_philosopher **philos)
{
	int i;
	struct timeval	actual_time;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i]->timelock);
		gettimeofday(&actual_time, NULL);
		if (get_time_lapse(actual_time, philos[i]->last_meal_time)
				>= common->time_to_die)
		{
			common->stop_simulation = true;
			break;
		}
		pthread_mutex_unlock(&philos[i]->timelock);
		i++;
	}
}
