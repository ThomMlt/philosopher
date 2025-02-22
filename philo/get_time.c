/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:04:31 by thomas            #+#    #+#             */
/*   Updated: 2025/02/22 16:10:19 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		time_ms;
	
	if (gettimeofday(&time, NULL) == -1)
		return (0);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms);
}