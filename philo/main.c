/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:29:49 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/22 12:34:12 by thomas           ###   ########.fr       */
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
	printf("\n time think %d", data.param->time_think);
}
