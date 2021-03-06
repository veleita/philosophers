/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 21:50:36 by mzomeno-          #+#    #+#             */
/*   Updated: 2021/11/10 12:14:51 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (1);
	else
		return (0);
}

int				ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

bool			ft_str_isdigit(char *str)
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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char		aux_char[1];

	if (n < 0)
	{
		nb = (unsigned int)(n * -1);
		aux_char[0] = '-';
		write(fd, aux_char, 1);
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		aux_char[0] = nb + '0';
		write(fd, aux_char, 1);
	}
}
