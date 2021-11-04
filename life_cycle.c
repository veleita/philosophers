/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:41:07 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/04 13:03:56 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	lock_fork(t_forks *forks, int fork_index)
{
	if (forks[fork_index]->status == AVAIABLE)
	{
		pthread_mutex_lock(forks[fork_index]->mutex);
		forks[fork_index]->status = BUSY;
		return (DONE);
	}
	else
		return (FAIL);
}

/*
** Left_fork = philo_id
** Right_fork = philo_id + 1 (or 0 for the last philo)
**
** If the philo manages to take both forks, print a message
** else, free the right fork and return
*/
void		take_forks(int philo_id, int last_philo, t_config *common)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_id;
	if (philo_id == last_philo)
		right_fork = 0;
	else
		right_fork = philo_id + 1;
	if (lock_fork(common->forks, left_fork) == FAIL)
		return;
	if (lock_fork(common->forks, right_fork) == FAIL)
		pthread_mutex_unlock(forks[left_fork]->mutex);
	else
		printer(FORKS_TAKEN, philo_id, common);
}

void	eat()
{
}

void	sleep()
{
}

void	think()
{
}
