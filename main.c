/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:14 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/11 10:44:05 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_config		common;
	t_philosopher	**philos;

	if (check_args(argv, argc) == CORRECT)
	{
		common = get_common(argv);
		philos = get_philos(&common);
		launch_philos(common.number_of_philosophers, philos);
		while (common.stop_simulation == false)
			check_stop_conditions(&common, philos);
	}
	else
	{
		printf("usage: ./philo "
			"[N_PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP]"
			" <optional>[N_MEALS]");
	}
	return (0);
}
