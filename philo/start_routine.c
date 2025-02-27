/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:31:18 by thomas            #+#    #+#             */
/*   Updated: 2025/02/27 16:49:59 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		message_fork(philo);
		pthread_mutex_unlock(philo->left_fork);
		message_fork(philo);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		message_fork(philo);
		pthread_mutex_lock(&philo->right_fork);
		message_fork(philo);
	}
}

void	eat_routine(t_philo *philo)
{
	if ((get_time_ms() - philo->last_time_meal) >= philo->param->time_die && philo->param->someone_died == FALSE)
		message_dead(philo);
	
	// // lock
	// if (check_if_simulation_ended(philo->param) == FALSE)
	// {
	// 	// unlock
	// 	take_fork(philo);
	// 	long long time = get_time_ms();
	// 	pthread_mutex_lock(&philo->param->mutex); 
	// 	philo->last_time_meal = time - philo->param->ms_time_start;
	// 	pthread_mutex_unlock(&philo->param->mutex);
	// 	message_eat(philo);
	// 	philo->nb_meal++;
	// 	usleep(philo->param->time_eat * 1000);
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	pthread_mutex_unlock(&philo->right_fork);
	// }
}

void	sleep_routine(t_philo *philo)
{
	if (check_if_simulation_ended(philo->param) == FALSE)
	{
		long long time = get_time_ms();
		message_sleep(philo);
		usleep(philo->param->time_sleep * 1000);
		philo->last_time_meal += time;
	}
}

void	think_routine(t_philo *philo)
{
	if (check_if_simulation_ended(philo->param) == FALSE)
	{
		long long time = get_time_ms();
		message_think(philo);
		usleep(philo->param->time_think * 1000);
		philo->last_time_meal += time;
	}
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(philo->param->time_eat * 1000);
	while (check_if_simulation_ended(philo->param) == FALSE)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

