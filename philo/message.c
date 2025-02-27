/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:17:43 by thomas            #+#    #+#             */
/*   Updated: 2025/02/27 16:49:33 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex);
	printf("%lld philo : %d has taken a fork\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->mutex);
}

void	message_eat(t_philo *philo)
{

		pthread_mutex_lock(&philo->param->mutex);
		printf("%lld philo : %d is eating\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
		pthread_mutex_unlock(&philo->param->mutex);
}

void	message_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex);
	printf("%lld philo : %d is sleeping\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->mutex);
}

void	message_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex);
	printf("%lld philo : %d is thinking\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->mutex);
}

void	message_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex);
	philo->param->someone_died = TRUE;
	printf("%lld philo : %d died\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->mutex);
}