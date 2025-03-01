/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:31:18 by thomas            #+#    #+#             */
/*   Updated: 2025/03/01 19:20:42 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_usleep(long long time_ms)
// {
// 	long long	start;

// 	start = get_time_ms();
// 	while ((get_time_ms() - start) < time_ms)
// 		usleep(50);
// 	// return (NULL);
// }

// void	eat_routine(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->right_fork);
// 	message_fork(philo);
// 	if (philo->param->nb_philo == 1)
// 	{
// 		ft_usleep(philo->param->time_die);
// 		pthread_mutex_unlock(&philo->right_fork);
// 		return ;
// 	}
// 	pthread_mutex_lock(philo->left_fork);
// 	message_fork(philo);
// 	message_eat(philo);
// 	pthread_mutex_lock(&philo->param->m_meal);
// 	philo->last_time_meal = get_time_ms();
// 	philo->nb_meal++;
// 	pthread_mutex_unlock(&philo->param->m_meal);
// 	ft_usleep(philo->param->time_eat);
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(&philo->right_fork);
// }

// void	sleep_routine(t_philo *philo)
// {
// 	message_sleep(philo);
// 	ft_usleep(philo->param->time_sleep);
// }

// void	think_routine(t_philo *philo)
// {
// 	message_think(philo);
// }

// int	end_loop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->param->m_dead);
// 	if (philo->param->end_simulation == 1)
// 	{
// 		pthread_mutex_unlock(&philo->param->m_dead);
// 		return (TRUE);
// 	}
// 	pthread_mutex_unlock(&philo->param->m_dead);
// 	return (FALSE);
// }

// void	*start_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 != 0)
// 		ft_usleep(philo->param->time_eat * 1000);
// 	while (end_loop(&philo[0]) == FALSE)
// 	{
// 		eat_routine(philo);
// 		sleep_routine(philo);
// 		think_routine(philo);
// 	}
// 	return (NULL);
// }

int	end_loop(t_philo *philo)
{
	if (philo->nb_meal == philo->param->nb_meal_to_finish)
		philo->param->finish_meal += 1;
	if (philo->param->finish_meal == philo->param->nb_meal_to_finish)
		return (TRUE);
	if ((get_time_ms() - philo->param->ms_time_start) - philo->last_time_meal >= philo->param->time_die)
	{
		message_dead(philo);
		return (TRUE);
	}
	return (FALSE);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	message_fork(philo);
	pthread_mutex_lock(philo->left_fork);
	message_fork(philo);
}

void	eat_routine(t_philo *philo)
{
	take_fork(philo);
	long long time = get_time_ms();
	philo->last_time_meal = time - philo->param->ms_time_start;
	message_eat(philo);
	philo->nb_meal += 1;
	usleep(philo->param->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	sleep_routine(t_philo *philo)
{
	long long time = get_time_ms();
	message_sleep(philo);
	usleep(philo->param->time_sleep * 1000);
	philo->last_time_meal += time;
}

void	think_routine(t_philo *philo)
{
	long long time = get_time_ms();
	message_think(philo);
	usleep(philo->param->time_think * 1000);
	philo->last_time_meal += time;
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(philo->param->time_eat * 1000);
	while (end_loop(philo) == FALSE)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
