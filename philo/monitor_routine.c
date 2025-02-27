/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:59 by thomas            #+#    #+#             */
/*   Updated: 2025/02/26 12:47:47 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_if_simulation_ended(t_param *param) 
{
    int ended;
    pthread_mutex_lock(&param->mutex);
    ended = param->end_simulation;
    pthread_mutex_unlock(&param->mutex);
    return (ended);
}

void set_simulation_ended(t_param *param) 
{
    pthread_mutex_lock(&param->mutex);
    param->end_simulation = TRUE;
    pthread_mutex_unlock(&param->mutex);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*args;
	t_data		*data;
	long long	last_meal_time;
	// int			nb_meal;
	int			i;
	
	args = (t_monitor *)arg;
	data = args->data;
	while (check_if_simulation_ended(data->param) == TRUE)
	{
		i = -1;
		while (i++ < data->param->nb_philo)
		{
			pthread_mutex_lock(&data->param->mutex);
			last_meal_time = data->philo[i]->last_time_meal;
			// nb_meal = data->philo[i]->nb_meal;
			pthread_mutex_unlock(&data->param->mutex);
			if (((get_time_ms() - data->param->ms_time_start - last_meal_time) >= data->param->time_die))
			{
				data->philo[i]->died = TRUE;
				message_dead(data->philo[i]);
				set_simulation_ended(data->param);
				break;
			}
		}
		usleep(10);
	}
	return (NULL);
}
