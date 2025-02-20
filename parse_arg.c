/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:09:51 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/19 19:36:47 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_int(long nb)
{
	if (nb > INT_MAX)
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 || ft_strlen(str) >= 10)
			return (0);
		i++;
	}
	return (1);
}

void	ft_parse_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (i < ac)
		{
			if (if_int(ft_atol(av[i])) == 0 || only_digit(av[i]) == 0)
			{
				printf("Argument must be an int");
				exit(1);
			}
			if (ft_atol(av[i]) < 0)
			{
				printf("Argument will be positive");
				exit(1);
			}
			i++;
		}
	}
	else
	{
		printf(ERR_ARG);
		exit(1);
	}
}
