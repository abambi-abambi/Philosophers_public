/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_lib_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:34:00 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi_ph(const char *str)
{
	int			i;
	t_atoi_ph	atoi;

	i = 0;
	atoi.num = 0;
	atoi.digits = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == ' ' || *str == '\r' || *str == '\f')
		str++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi.num = atoi.num * 10 + (str[i] - '0');
		atoi.digits++;
		i++;
	}
	if ((str[i] >= 32 && str[i] <= 127) || atoi.digits > 10 || \
		(atoi.num) > 2147483647)
		return (-1);
	return ((int)atoi.num);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
