/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:17:43 by thomas            #+#    #+#             */
/*   Updated: 2025/03/03 14:38:28 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->m_write);
	if (end_loop(philo->param) == FALSE)
		printf("%lld philo : %d has taken a fork\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->m_write);
}

void	message_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->m_write);
	if (end_loop(philo->param) == FALSE)
		printf("%lld philo : %d is eating\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->m_write);
}

void	message_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->m_write);
	if (end_loop(philo->param) == FALSE)
		printf("%lld philo : %d is sleeping\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->m_write);
}

void	message_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->m_write);
	if (end_loop(philo->param) == FALSE)
		printf("%lld philo : %d is thinking\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->m_write);
}

void	message_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->m_write);
	if (end_loop(philo->param) == TRUE)
		printf("%lld philo : %d died\n", (get_time_ms() - philo->param->ms_time_start), philo->id);
	pthread_mutex_unlock(&philo->param->m_write);
}
