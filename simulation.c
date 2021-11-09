/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:11:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/09 13:33:31 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** PHILO THREAD
*/

bool	the_philo_needs_to_eat(struct timeval last_meal_time, int time_to_die,
		int time_to_eat, int time_to_sleep)
{
	struct timeval	actual_time;
	long int		time_of_starvation;
	long int		time_left;
	int			time_to_digest;

	gettimeofday(&actual_time, NULL);
	time_of_starvation = get_time_lapse(actual_time, last_meal_time);
	time_left = time_to_die - time_of_starvation;
	time_to_digest = time_to_eat + time_to_sleep + 100;
	if (time_left <= time_to_digest)
		return (true);
	else
		return (false);
}

static void	live(t_philosopher *stats)
{
//	if (the_philo_needs_to_eat(stats->last_meal_time,
//				stats->common->time_to_die,
//				stats->common->time_to_eat,
//				stats->common->time_to_sleep))
//	{
	philo_eat(stats->id, stats->common->number_of_philosophers - 1,
				stats->common, stats);
//		philo_sleep(stats->id, stats->common);
	printer(THINK, stats->id, stats->common);
//	}
}

void	*start_routine(void *arg)
{
	t_philosopher	*stats;

	stats = (t_philosopher *)arg;
	while (stats->common->stop_simulation == false)
		live(arg);
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
			printer(DIE, i, common);
		}
		pthread_mutex_unlock(&philos[i]->timelock);
		i++;
	}
}
