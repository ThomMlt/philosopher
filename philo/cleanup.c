/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:24:11 by thomas            #+#    #+#             */
/*   Updated: 2025/02/25 14:36:34 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	cleanup_free(t_data *data)
// {
// 	int	i;
// 	int	nb_philo;

// 	i = 0;
// 	nb_philo = data->param->nb_philo;
// 	free(data->param);
// 	while (i < nb_philo)
// 	{
// 		// pthread_mutex_destroy(&data->philo[i]->left_fork);
//         // pthread_mutex_destroy(&data->philo[i]->right_fork);
// 		free(data->philo[i]);
// 		i++;
// 	}
// 	free(data->philo);
// }

void cleanup_free(t_data *data) {
    int i;
    int nb_philo;

    i = 0;
    nb_philo = data->param->nb_philo;

    // Destruction du mutex avant de libérer la mémoire
    pthread_mutex_destroy(&data->param->mutex);
	
	int j = 0;
	while (j < data->param->nb_philo)
	{
        pthread_mutex_destroy(&data->philo[j]->right_fork);
		j++;
	}
    free(data->param);
    while (i < nb_philo) {
        free(data->philo[i]);
        i++;
    }
    free(data->philo);
}