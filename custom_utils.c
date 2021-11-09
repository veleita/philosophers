/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:31:43 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/09 13:05:56 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	time_struct_to_int(struct timeval s)
{
	return (s.tv_sec * 1000 + s.tv_usec / 1000);
}

long int	get_time_lapse(struct timeval t1, struct timeval t2)
{
	return (time_struct_to_int(t1) - time_struct_to_int(t2));
}

void	printer(const char *message, int philo_id, t_config *common)
{
	struct timeval	time;

	pthread_mutex_lock(&common->printer);
	gettimeofday(&time, NULL);
	if (common->stop_simulation == false || !ft_strcmp(DIE, message))
		printf("[%li] Philosopher %i %s  FORKL: %d  FORKR: %d\n",
			get_time_lapse(time, common->start_time),
			philo_id, message,
			common->forks[philo_id]->state,
			common->forks[philo_id + 1]->state);
	pthread_mutex_unlock(&common->printer);
}

void	ft_usleep(int ms, bool *stop_simulation)
{
	struct timeval	init;
	struct timeval	current;

	gettimeofday(&init, NULL);
	gettimeofday(&current, NULL);
	while (*stop_simulation == false && get_time_lapse(current, init) < ms)
	{
		usleep(1);
		gettimeofday(&current, NULL);
	}
}
