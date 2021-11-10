/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 23:11:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/10 16:34:36 by mzomeno-         ###   ########.fr       */
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
	if (time_left <= time_to_digest * 0.5)
		return (true);
	else
		return (false);
}

static void	live(t_philosopher *stats)
{
	if (the_philo_needs_to_eat(stats->last_meal_time,
				stats->common->time_to_die,
				stats->common->time_to_eat,
				stats->common->time_to_sleep))
	{
		eat_and_sleep(stats->id, stats->common->number_of_philosophers - 1,
				stats->common, stats);
		printer(THINK, stats->id, stats->common);
	}
}

void	*start_routine(void *arg)
{
	t_philosopher	*stats;

	stats = (t_philosopher *)arg;
//	eat_and_sleep(stats->id, stats->common->number_of_philosophers - 1,
//			stats->common, stats);
//	printer(THINK, stats->id, stats->common);
	while (stats->common->stop_simulation == false)
	{
		live(arg);
	}
	return (NULL);
}

/*
** MAIN THREAD
*/
static void	check_number_of_meals(t_config *common, bool *have_eaten_n_times,
		t_philosopher **philos)
{
	int i;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		if (have_eaten_n_times[i] == false)
			return;
		i++;
	}
	common->number_of_meals++;
	if (common->number_of_meals == common->number_of_times_each_philosopher_must_eat)
	{
		common->stop_simulation = true;
		terminate(philos, common);
	}
}

void	check_stop_conditions(t_config *common, t_philosopher **philos)
{
	int i;
	struct timeval	actual_time;
	bool		*have_eaten_n_times;

	have_eaten_n_times = (bool *)malloc(sizeof(bool) * common->number_of_philosophers);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		have_eaten_n_times[i] = false;
		pthread_mutex_lock(&philos[i]->timelock);
		gettimeofday(&actual_time, NULL);
		if (get_time_lapse(actual_time, philos[i]->last_meal_time)
				>= common->time_to_die + 10)
			return (death(i, common, philos, have_eaten_n_times));
		if (philos[i]->number_of_meals > common->number_of_meals)
			have_eaten_n_times[i] = true;
		pthread_mutex_unlock(&philos[i]->timelock);
		i++;
	}
	check_number_of_meals(common, have_eaten_n_times, philos);
	free(have_eaten_n_times);
}
