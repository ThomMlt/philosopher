/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:24:44 by thomas            #+#    #+#             */
/*   Updated: 2025/02/26 11:25:14 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_data *data)
{
	int	i;
	pthread_t	monitor;
	t_monitor	*monitor_data;

	i = 0;
	monitor_data = malloc(sizeof(t_monitor));
	monitor_data->data = data;
	while (i < data->param->nb_philo)
	{
		pthread_create(&data->philo[i]->thread, NULL, start_routine, data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, monitor_data);
	i = 0;
	while (i < data->param->nb_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
}