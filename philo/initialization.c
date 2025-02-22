/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:04:03 by thomas            #+#    #+#             */
/*   Updated: 2025/02/22 11:23:20 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct_param(t_data *data, int ac, char **av)
{
	data->param = malloc(sizeof(t_param));
	if (!data->param)
		return (FAIL);
	data->param->nb_philo = ft_atol(av[1]);
	data->param->time_die = ft_atol(av[2]);
	data->param->time_eat = ft_atol(av[3]);
	data->param->time_sleep = ft_atol(av[4]);
	data->param->time_think = 1;
	if (ac == 6)
		data->param->nb_meal = ft_atol(av[5]);
	return (SUCCESS);
}

int	init_struct_philo(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->param->nb_philo + 1);
	if (!data->philo)
		return (FAIL);
	return (SUCCESS);	
}
