/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:04:03 by thomas            #+#    #+#             */
/*   Updated: 2025/02/23 17:26:17 by thomas           ###   ########.fr       */
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
	data->param->ms_time_start = get_time_ms();
	if (ac == 6)
		data->param->nb_meal = ft_atol(av[5]);
	return (SUCCESS);
}

int	init_struct_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->param->nb_philo));
	if (!data->philo)
		return (FAIL);
	while (i < data->param->nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->philo[i]->id = 1 + i;
		data->philo[i]->nb_meal = 0;
		data->philo[i]->last_time_meal = get_time_ms();
		data->philo[i]->left_fork = NULL;
		pthread_mutex_init(&data->philo[i]->right_fork, NULL);
		if (i == data->param->nb_philo - 1)
			data->philo[i]->left_fork = &data->philo[0]->right_fork;
		else
			data->philo[i]->left_fork = &data->philo[i + 1]->right_fork;
		data->philo[i]->param = data->param;
		i++;
	}
	return (SUCCESS);	
}
