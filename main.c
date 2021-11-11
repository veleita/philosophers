/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:14 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/11 09:56:19 by mzomeno-         ###   ########.fr       */
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

	common = get_common(argv);
	philos = get_philos(&common);
	launch_philos(common.number_of_philosophers, philos);
	while (common.stop_simulation == false)
		check_stop_conditions(&common, philos);
	return (0);
}
