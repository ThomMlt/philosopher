/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:59 by thomas            #+#    #+#             */
/*   Updated: 2025/03/03 18:44:01 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(&philo->param->m_meal);
	if (get_time_ms() - philo->last_time_meal >= time_to_die)
	{
		pthread_mutex_unlock(&philo->param->m_meal);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->param->m_meal);
	return (FALSE);
}

int		check_someone_dead(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos[0].param->m_dead);
	while (i < philos[0].param->nb_philo)
	{
		if (philosopher_dead(&philos[i], philos[0].param->time_die) == TRUE)
		{
			message_dead(&philos[i]);
			philos[0].param->end_simulation = TRUE;
			pthread_mutex_unlock(&philos[0].param->m_dead);
			return (TRUE);
		}
		i++;
	}
	pthread_mutex_unlock(&philos[0].param->m_dead);
	return (FALSE);
}

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].param->nb_meal_to_finish == -1)
		return (FALSE);
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
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		// printf("\n ici on regarde le resultat de someone_dead %d\n", check_someone_dead(philo));
		if (check_someone_dead(philo) == TRUE || check_all_ate(philo) == TRUE)
			break;
	}
	return (NULL);
}