/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:24:11 by thomas            #+#    #+#             */
/*   Updated: 2025/02/22 16:04:19 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_free(t_data *data)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = data->param->nb_philo;
	free(data->param);
	while (i < nb_philo)
	{
		// pthread_mutex_destroy(&data->philo[i]->left_fork);
        // pthread_mutex_destroy(&data->philo[i]->right_fork);
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
}