/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:17:55 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/10/29 18:33:44 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

bool			ft_isdigit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

unsigned int	ft_atoi(char *str)
{
	unsigned int i;

	if (!ft_isdigit(str))
		return (0);
	i = 0;
	while (*str != '\0')
	{
		i += (*str - '0');
		i *= 10;
		if (i > INT_MAX)
			return (0);
		str++;
	}
	i /= 10;
	return (i);
}

t_config	parse(char **argv)
{
	t_config	configuration;

	configuration.number_of_philosophers = ft_atoi(argv[1]);
	configuration.time_to_die = ft_atoi(argv[2]);
	configuration.time_to_eat = ft_atoi(argv[3]);
	configuration.time_to_sleep = ft_atoi(argv[4]);
	return (configuration);	
}
