/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:42:28 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/18 17:35:14 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi_philo(char *nb)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (ft_strlen(nb) <= 11)
	{
		if (nb[i] == '+' || nb[i] == '-')
		{
			if (nb[i] == '-' && nb[i + 1] != '-')
				return (printf("time must be postive"), exit(0), 0);
			i++;
		}
		while (nb[i] >= '0' && nb[i] <= '9')
		{
			res = res * 10 + nb[i] - '0';
			i++;
		}
		if (res > 2147483647)
			return (printf("time must be contained in an int"), exit(0), 0);
		return (res);
	}
	else
		return (printf("time must be contained in an int"), exit(0), 0);
}
