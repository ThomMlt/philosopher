/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:35:10 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/19 19:27:28 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define ERR_ARG "./philo number_of_philosophers time_to_die time_to_eat time_to_sleep (option : number_of_times_each_philosopher_must_eat)"

/* basique utils */
int	ft_strlen(char *str);
long	ft_atol(char *nb);

/*hangling arg*/
int		if_int(long nb);
void	ft_parse_arg(int ac, char **av);

#endif