/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:16:20 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/10/29 18:33:07 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>	// INT_MAX
# include <stdbool.h>	// bool type
# include <pthread.h>	// threads and mutex
# include <string.h>	// memset
# include <unistd.h>	// write
# include <stdlib.h>	// malloc, free

typedef struct 	s_config
{
		int		number_of_philosophers;
		int		time_to_die;
		int		time_to_eat;
		int		time_to_sleep;
}				t_config;


/*
** init.c
*/
t_config	parse(char **argv);

#endif
