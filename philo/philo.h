/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:35:10 by tmillot           #+#    #+#             */
/*   Updated: 2025/03/01 18:57:12 by thomas           ###   ########.fr       */
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
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					time_think;
	long long			ms_time_start;
	int					nb_meal_to_finish;
	int					finish_meal;
	int					end_simulation;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_meal;
	pthread_mutex_t		m_write;
}	t_param;

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	long long			last_time_meal;
	pthread_t			thread;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	t_param				*param;
}	t_philo;

typedef struct s_data
{
	t_param				*param;
	t_philo				**philo;
}				t_data;

typedef struct s_monitor
{
	t_data *data;
}	t_monitor;



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

/* get time in millisecond*/
long long	get_time_ms(void);

/* Handling free */
void	cleanup_free(t_data *data);

/* pthread */
void	create_thread(t_data *data);

/* Message */
void	message_fork(t_philo *philo);
void	message_eat(t_philo *philo);
void	message_sleep(t_philo *philo);
void	message_think(t_philo *philo);
void	message_dead(t_philo *philo);

/* Philo routine */
void	*start_routine(void *arg);
void	think_routine(t_philo *philo);
void	sleep_routine(t_philo *philo);
void	eat_routine(t_philo *philo);
void	take_fork(t_philo *philo);

/* monitor routine */
void	*monitor_routine(void *arg);
int	end_loop(t_philo *philo);

#endif