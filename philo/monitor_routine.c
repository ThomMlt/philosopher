/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:59 by thomas            #+#    #+#             */
/*   Updated: 2025/03/04 13:48:48 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.param->m_meal);
	if (get_time_ms() - philo.last_time_meal >= philo.param->time_die)
	{
		pthread_mutex_unlock(&philo.param->m_meal);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo.param->m_meal);
	return (FALSE);
}

int		check_someone_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param->nb_philo)
	{
		if (philosopher_dead(*data->philo[i]) == TRUE)
		{
			pthread_mutex_lock(&data->param->m_dead);
			printf("%lld philo : %d died\n", (get_time_ms() - data->philo[i]->param->ms_time_start), data->philo[i]->id);
			data->param->end_simulation = TRUE;
			pthread_mutex_unlock(&data->param->m_dead);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (data->param->nb_meal_to_finish == -1)
		return (FALSE);
	while (i < data->param->nb_philo)
	{
		pthread_mutex_lock(&data->param->m_meal);
		if (data->philo[i]->nb_meal >= data->param->nb_meal_to_finish)
			finished_eating++;
		pthread_mutex_unlock(&data->param->m_meal);
		i++;
	}
	if (finished_eating == data->param->nb_philo)
	{
		pthread_mutex_lock(&data->param->m_dead);
		data->param->end_simulation = TRUE;
		pthread_mutex_unlock(&data->param->m_dead);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (TRUE)
	{
		// printf("\n ici on regarde le resultat de someone_dead %d\n", check_someone_dead(philo));
		if (check_someone_dead(data) == TRUE || check_all_ate(data) == TRUE)
			break;
	}
	return (NULL);
}