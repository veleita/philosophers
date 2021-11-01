/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:14 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/01 19:03:44 by mzomeno-         ###   ########.fr       */
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
	pthread_mutex_t	**forks;
	t_philosopher	**philos;

	if (!(argc == 4 || argc == 5))
		exit(1);

	common = parse(argv);
	forks = get_forks(common.number_of_philosophers);
	philos = get_philos(&common);
	simulation(&common, philos, forks);

	printf("%d, %d, %d, %d",
			common.number_of_philosophers,
			common.time_to_die,
			common.time_to_eat,
			common.time_to_sleep);
	return (0);
}
