/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:31:18 by thomas            #+#    #+#             */
/*   Updated: 2025/03/03 18:39:38 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time_ms)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time_ms)
		usleep(50);
	// return (NULL);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	message_fork(philo);
	if (philo->param->nb_philo == 1)
	{
		ft_usleep(philo->param->time_die);
		pthread_mutex_unlock(&philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	message_fork(philo);
	message_eat(philo);
	pthread_mutex_lock(&philo->param->m_meal);
	philo->last_time_meal = get_time_ms();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->param->m_meal);
	ft_usleep(philo->param->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	sleep_routine(t_philo *philo)
{
	message_sleep(philo);
	ft_usleep(philo->param->time_sleep);
}

void	think_routine(t_philo *philo)
{
	message_think(philo);
}

int	end_loop(t_param *param)
{
	int	end_simulation;
	
	pthread_mutex_lock(&param->m_dead);
	end_simulation = param->end_simulation;
	pthread_mutex_unlock(&param->m_dead);
	return (end_simulation);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->id % 2 != 0)
	// 	ft_usleep(philo->param->time_eat * 1000);
	while (end_loop(philo->param) == FALSE)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
		printf("resultat de end_loop apres un cycle d'un philo : %d\n", end_loop(philo->param));
	}
	return (NULL);
}
