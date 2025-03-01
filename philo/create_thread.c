/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:24:44 by thomas            #+#    #+#             */
/*   Updated: 2025/03/01 19:19:59 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	create_thread(t_data *data)
// {
// 	int	i;
// 	pthread_t	monitor;

// 	i = 0;
// 	while (i < data->param->nb_philo)
// 	{
// 		pthread_create(&data->philo[i]->thread, NULL, start_routine, data->philo[i]);
// 		i++;
// 	}
// 	pthread_create(&monitor, NULL, monitor_routine, data->philo);
// 	i = 0;
// 	while (i < data->param->nb_philo)
// 	{
// 		pthread_join(data->philo[i]->thread, NULL);
// 		i++;
// 	}
// }

void	create_thread(t_data *data)
{
	int	i;
	pthread_t	monitor;

	i = 0;
	while (i < data->param->nb_philo)
	{
		if (pthread_create(&data->philo[i]->thread, NULL, start_routine, data->philo[i]) != 0)
			exit_erreur("Failed to create thread");
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		exit_erreur("Failed to create monitor thread");
	i = 0;
	while (i < data->param->nb_philo)
	{
		if (pthread_join(data->philo[i]->thread, NULL) != 0)
			exit_erreur("Failed to join thread");
		i++;
	}
}
