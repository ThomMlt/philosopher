/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:31:18 by thomas            #+#    #+#             */
/*   Updated: 2025/02/23 18:24:32 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	printf("le philo %d prend une fourchette 1\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("le philo %d prend une fourchette 2\n", philo->id);
}

void	eat_routine(t_philo *philo)
{
	take_fork(philo);
	if (philo->id % 2 == 1)
		usleep(philo->param->time_eat * 1000);
	long long time = get_time_ms();
	printf("le philo : %d mange au temp %lld\n", philo->id, (time - philo->param->ms_time_start));
	usleep(philo->param->time_eat * 1000);
	// pthread_mutex_unlock(&philo->right_fork);
	// pthread_mutex_unlock(philo->left_fork);
}

void	sleep_routine(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	long long time = get_time_ms();
	printf("le philo : %d dort au temp %lld\n", philo->id, (time - philo->param->ms_time_start));
	usleep(philo->param->time_sleep * 1000);
}

void	think_routine(t_philo *philo)
{
	long long time = get_time_ms();
	printf("le philo : %d pense au temp %lld\n", philo->id, (time - philo->param->ms_time_start));
	usleep(philo->param->time_think * 1000);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(philo->param->time_eat * 1000);
	while (1)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param->nb_philo)
	{
		pthread_create(&data->philo[i]->thread, NULL, start_routine, data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->param->nb_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
}