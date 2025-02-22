/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:29:49 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/22 16:43:57 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	data;

	ft_parse_arg(ac, av);
	if (init_struct_param(&data, ac, av) == FAIL || init_struct_philo(&data) == FAIL)
		exit_erreur(ERR_MALLOC);
	printf("\n nb philo %d", data.param->nb_philo);
	printf("\n time die %d", data.param->time_die);
	printf("\n time eat %d", data.param->time_eat);
	printf("\n time sleep %d", data.param->time_sleep);
	printf("\n time think %d\n", data.param->time_think);
	printf("\n time %lld\n", data.param->ms_time_start);
	int i = 0;
	while (i < data.param->nb_philo)
	{
		printf("le philo[%d] a l'id : %d\n", i, data.philo[i]->id);
		i++;
	}
	cleanup_free(&data);
}
