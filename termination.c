/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <1veleita1@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:05:20 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/10 12:49:39 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	terminate(t_philosopher **philos, t_config *common)
{
	int	i;

	i = 0;
	while (i < common->number_of_philosophers)
		pthread_join(*philos[i++]->thread, NULL);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		free(philos[i]->thread);
		free(philos[i]);
		pthread_mutex_destroy(common->forks[i]->mutex);
		free(common->forks[i]);
		i++;
	}
	free(common->forks);
	free(philos);
	printf("Simulation end\n");
	pthread_mutex_destroy(&common->printer);
	free(common);
}

void		death(int dead_philo_id, t_config *common, t_philosopher **philos)
{
	common->stop_simulation = true;
	printer(DIE, dead_philo_id, common);
	pthread_mutex_unlock(&philos[dead_philo_id]->timelock);
	terminate(philos, common);
}
