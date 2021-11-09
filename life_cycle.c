/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:41:07 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/09 17:03:09 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	lock_fork(t_fork **forks, int fork_index)
{
	if (forks[fork_index]->state == AVAIABLE)
	{
		pthread_mutex_lock(forks[fork_index]->mutex);
		forks[fork_index]->state = TAKEN;
		return (DONE);
	}
	else
		return (FAIL);
}

static void	just_eat(t_philosopher *stats)
{
	pthread_mutex_lock(&stats->timelock);
	stats->number_of_meals++;
	printer(EAT, stats->id, stats->common);
	gettimeofday(&stats->last_meal_time, NULL);
	pthread_mutex_unlock(&stats->timelock);
	ft_usleep(stats->common->time_to_eat, &(stats->common->stop_simulation));
}

static void	release_forks(t_fork **forks, int left_fork, int right_fork)
{
	pthread_mutex_unlock(forks[right_fork]->mutex);
	pthread_mutex_unlock(forks[left_fork]->mutex);
	forks[right_fork]->state = AVAIABLE;
	forks[left_fork]->state = AVAIABLE;
}
/*
** Left_fork = philo_id
** Right_fork = philo_id + 1 (or 0 for the last philo)
**
** If the philo manages to take both forks, print a message
** else, free the right fork and return
*/
void	philo_eat(int philo_id, int last_philo, t_config *common,
		t_philosopher *stats)
{
	int		left_fork;
	int		right_fork;
	bool	left_fork_taken;
	bool	right_fork_taken;

	left_fork = philo_id;
	if (philo_id == last_philo)
		right_fork = 0;
	else
		right_fork = philo_id + 1;
	left_fork_taken = false;
	right_fork_taken = false;
	while (left_fork_taken == false || right_fork_taken == false)
	{
		if (right_fork_taken == true)
		{
			pthread_mutex_unlock(common->forks[right_fork]->mutex);
			common->forks[right_fork]->state = AVAIABLE;
		}
		else if (left_fork_taken == true)
		{
			pthread_mutex_unlock(common->forks[left_fork]->mutex);
			common->forks[left_fork]->state = AVAIABLE;
		}
		left_fork_taken = (bool)lock_fork(common->forks, left_fork);
		right_fork_taken = (bool)lock_fork(common->forks, right_fork);
	}
	printer(FORKS, philo_id, common);
	just_eat(stats);
//	printer(FORKSNT, philo_id, common);
	release_forks(common->forks, left_fork, right_fork);
	printer(SLEEP, philo_id, common);
	ft_usleep(common->time_to_sleep, &(common->stop_simulation));
	printer(WAKE, philo_id, common);
//	philo_sleep(philo_id, common);
}

void	philo_sleep(int philo_id, t_config *common)
{
	printer(SLEEP, philo_id, common);
	ft_usleep(common->time_to_sleep, &(common->stop_simulation));
	printer(WAKE, philo_id, common);
}
