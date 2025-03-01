/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:04:03 by thomas            #+#    #+#             */
/*   Updated: 2025/03/01 19:08:03 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	init_struct_param(t_data *data, int ac, char **av)
// {
// 	data->param = malloc(sizeof(t_param));
// 	if (!data->param)
// 		return (FAIL);
// 	data->param->nb_philo = ft_atol(av[1]);
// 	data->param->time_die = ft_atol(av[2]);
// 	data->param->time_eat = ft_atol(av[3]);
// 	data->param->time_sleep = ft_atol(av[4]);
// 	data->param->time_think = 1;
// 	data->param->ms_time_start = get_time_ms();
// 	data->param->finish_meal = 0;
// 	data->param->end_simulation = FALSE;
// 	pthread_mutex_init(&data->param->m_dead, NULL);
// 	pthread_mutex_init(&data->param->m_meal, NULL);
// 	pthread_mutex_init(&data->param->m_write, NULL);
// 	if (ac == 6)
// 		data->param->nb_meal_to_finish = ft_atol(av[5]);
// 	else
// 		data->param->nb_meal_to_finish = -1;
// 	return (SUCCESS);
// }

// static void	init_tab_philo(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	i = 0;
// 	while (i < data->param->nb_philo)
// 	{
// 		data->philo[i]->id = 1 + i;
// 		data->philo[i]->nb_meal = 0;
// 		data->philo[i]->last_time_meal = get_time_ms();
// 		data->philo[i]->left_fork = NULL;
// 		pthread_mutex_init(&data->philo[i]->right_fork, NULL);
// 		if (i == (data->param->nb_philo - 1))
// 			data->philo[i]->left_fork = &data->philo[0]->right_fork;
// 		else
// 			data->philo[i]->left_fork = &data->philo[i + 1]->right_fork;
// 		data->philo[i]->param = data->param;
// 		i++;
// 	}
// }

// int	init_struct_philo(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->philo = malloc(sizeof(t_philo) * (data->param->nb_philo + 1));
// 	if (!data->philo)
// 		return (FAIL);
// 	data->philo[data->param->nb_philo] = NULL;
// 	while (i < data->param->nb_philo)
// 	{
// 		data->philo[i] = malloc(sizeof(t_philo));
// 		i++;
// 	}
// 	init_tab_philo(data);
// 	return (SUCCESS);	
// }

int	init_struct_param(t_data *data, int ac, char **av)
{
	data->param = malloc(sizeof(t_param));
	if (!data->param)
		return (FAIL);
	data->param->nb_philo = ft_atol(av[1]);
	data->param->time_die = ft_atol(av[2]);
	data->param->time_eat = ft_atol(av[3]);
	data->param->time_sleep = ft_atol(av[4]);
	data->param->time_think = 1;
	data->param->ms_time_start = get_time_ms();
	data->param->finish_meal = 0;
	data->param->end_simulation = FALSE;

	// Vérification de l'initialisation des mutex
	if (pthread_mutex_init(&data->param->m_dead, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(&data->param->m_meal, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(&data->param->m_write, NULL) != 0)
		return (FAIL);

	if (ac == 6)
		data->param->nb_meal_to_finish = ft_atol(av[5]);
	else
		data->param->nb_meal_to_finish = -1;
	return (SUCCESS);
}

static void	init_tab_philo(t_data *data)
{
	int	i;

	i = 0;
	i = 0;
	while (i < data->param->nb_philo)
	{
		data->philo[i]->id = 1 + i;
		data->philo[i]->nb_meal = 0;
		data->philo[i]->last_time_meal = get_time_ms();
		data->philo[i]->left_fork = NULL;
		
		// Vérification de l'initialisation du mutex
		if (pthread_mutex_init(&data->philo[i]->right_fork, NULL) != 0)
			exit_erreur("Mutex initialization failed");

		if (i == (data->param->nb_philo - 1))
			data->philo[i]->left_fork = &data->philo[0]->right_fork;
		else
			data->philo[i]->left_fork = &data->philo[i + 1]->right_fork;
		data->philo[i]->param = data->param;
		i++;
	}
}

int	init_struct_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->param->nb_philo + 1));
	if (!data->philo)
		return (FAIL);
	data->philo[data->param->nb_philo] = NULL;
	while (i < data->param->nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (FAIL);
		i++;
	}
	init_tab_philo(data);
	return (SUCCESS);	
}