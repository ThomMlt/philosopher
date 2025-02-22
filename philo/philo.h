/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:35:10 by tmillot           #+#    #+#             */
/*   Updated: 2025/02/22 11:30:28 by thomas           ###   ########.fr       */
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
# define SUCCESS 0
# define FAIL 1
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define ERR_MALLOC "error in initialization struct (fail malloc)"
# define ERR_ARG "./philo number_of_philosophers time_to_die time_to_eat time_to_sleep (option : number_of_times_each_philosopher_must_eat)"

typedef struct s_param
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		time_think;
	int		nb_meal;
}	t_param;

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	pthread_t			process;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
}	t_philo;

typedef struct s_data
{
	t_param				*param;
	t_philo				**philo;
}				t_data;


/* basique utils */
int	ft_strlen(char *str);
long	ft_atol(char *nb);

/*hangling arg*/
int		if_int(long nb);
void	ft_parse_arg(int ac, char **av);

/* inti structure */
int	init_struct_param(t_data *data, int ac, char **av);
int	init_struct_philo(t_data *data);

/* Hangling return error */
void exit_erreur(char *str);

#endif