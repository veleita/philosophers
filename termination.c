/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:10:04 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/11 17:49:35 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	terminate(t_philosopher **philos, t_config *common)
{
	int	i;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_unlock(common->forks[i]->mutex);
		if (i == common->number_of_philosophers - 1)
			pthread_mutex_unlock(common->forks[0]->mutex);
		else
			pthread_mutex_unlock(common->forks[i + 1]->mutex);
		pthread_join(*philos[i++]->thread, NULL);
	}
	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos[i]->timelock);
		free(philos[i]->thread);
		free(philos[i]);
		pthread_mutex_destroy(common->forks[i]->mutex);
		free(common->forks[i]);
		i++;
	}
	free(common->forks);
	free(philos);
	pthread_mutex_destroy(&common->printer);
}

void	death(int dead_philo_id, t_config *common,
					t_philosopher **philos, bool *have_eaten_n_times)
{
	common->stop_simulation = true;
	free(have_eaten_n_times);
	printer(DIE, dead_philo_id, common);
	pthread_mutex_unlock(&philos[dead_philo_id]->timelock);
	terminate(philos, common);
}

/* Such a patch */
int	one_philo(int time_to_die)
{
	printf("[%d] Philosopher 0 died\n", time_to_die);
	printf("---------------THE END---------------\n");
	return (0);
}
