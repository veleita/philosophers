/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:14 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/03 10:53:24 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

/*
 * parse = argv to struct
 */

int main(int argc, char **argv)
{
	t_config		common;
	t_philosopher	**philos;

	if (!(argc == 5 || argc == 6))
		exit(1);

	common = parse(argv);
	common.forks = get_forks(common.number_of_philosophers);
	common.stop_simulation = false;
	philos = get_philos(&common);
	launch_philos(common.number_of_philosophers, philos);
	while (common.stop_simulation == false)
		check_stop_conditions(&common, philos);

	/*
	printf("%d, %d, %d, %d",
			common.number_of_philosophers,
			common.time_to_die,
			common.time_to_eat,
			common.time_to_sleep);
	*/
	return (0);
}
