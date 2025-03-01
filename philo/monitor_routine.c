/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:59 by thomas            #+#    #+#             */
/*   Updated: 2025/03/01 19:03:11 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int check_if_simulation_ended(t_param *param) 
// {
//     int ended;
//     pthread_mutex_lock(&param->mutex);
//     ended = param->end_simulation;
//     pthread_mutex_unlock(&param->mutex);
//     return (ended);
// }

// void set_simulation_ended(t_param *param) 
// {
//     pthread_mutex_lock(&param->mutex);
//     param->end_simulation = TRUE;
//     pthread_mutex_unlock(&param->mutex);
// }

// void	*monitor_routine(void *arg)
// {
// 	t_monitor	*args;
// 	t_data		*data;
// 	long long	last_meal_time;
// 	// int			nb_meal;
// 	int			i;
	
// 	args = (t_monitor *)arg;
// 	data = args->data;
// 	while (check_if_simulation_ended(data->param) == TRUE)
// 	{
// 		i = -1;
// 		while (i++ < data->param->nb_philo)
// 		{
// 			pthread_mutex_lock(&data->param->mutex);
// 			last_meal_time = data->philo[i]->last_time_meal;
// 			// nb_meal = data->philo[i]->nb_meal;
// 			pthread_mutex_unlock(&data->param->mutex);
// 			if (((get_time_ms() - data->param->ms_time_start - last_meal_time) >= data->param->time_die))
// 			{
// 				data->philo[i]->died = TRUE;
// 				message_dead(data->philo[i]);
// 				set_simulation_ended(data->param);
// 				break;
// 			}
// 		}
// 		usleep(10);
// 	}
// 	return (NULL);
// }

int	philosopher_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(&philo->param->m_meal);
	if (get_time_ms() - philo->last_time_meal >= time_to_die)
	{
		pthread_mutex_unlock(&philo->param->m_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->param->m_meal);
	return (0);
}

int		check_someone_dead(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos[0].param->m_dead);
	while (i < philos[0].param->nb_philo)
	{
		if (philosopher_dead(&philos[i], philos[0].param->nb_philo) == 1)
		{
			message_dead(&philos[i]);
			philos[0].param->end_simulation = TRUE;
			pthread_mutex_unlock(&philos[0].param->m_dead);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philos[0].param->m_dead);
	return (0);
}

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].param->nb_meal_to_finish == -1)
		return (0);
	while (i < philos[0].param->nb_philo)
	{
		pthread_mutex_lock(&philos[i].param->m_meal);
		if (philos[i].nb_meal >= philos[i].param->nb_meal_to_finish)
			finished_eating++;
		pthread_mutex_unlock(&philos[i].param->m_meal);
		i++;
	}
	if (finished_eating == philos[0].param->nb_philo)
	{
		pthread_mutex_lock(&philos[i].param->m_dead);
		philos[0].param->end_simulation = TRUE;
		pthread_mutex_unlock(&philos[i].param->m_dead);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (check_someone_dead(philo) == 1 || check_all_ate(philo) == 1)
			break;
	}
	return (NULL);
}