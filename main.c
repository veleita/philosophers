/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:37:14 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/10/29 18:32:44 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

/*
 * parse = argv to struct
 */

int main(int argc, char **argv)
{
	t_config	configuration;

	if (!(argc == 4 || argc == 5))
		exit(1);

	configuration = parse(argv);

	printf("%d, %d, %d, %d",
			configuration.number_of_philosophers,
			configuration.time_to_die,
			configuration.time_to_eat,
			configuration.time_to_sleep);
	return (0);
}
