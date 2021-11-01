/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 21:50:36 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/01 13:53:36 by mzomeno-         ###   ########.fr       */
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
