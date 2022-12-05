/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/10/05 18:31:34 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_args	t_args;
typedef struct s_time	t_time;

typedef struct s_time
{
	struct timeval	*time_from_start;
	struct timeval	time_now;
	suseconds_t		time_in_ms;
	suseconds_t		end_of_meal;
}				t_time;

typedef struct s_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
}				t_args;

typedef struct s_philo
{
	t_data			*data;
	t_time			time;
	int				*philo_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_philo;

typedef struct s_data
{
	t_philo			*p;
	t_args			args;
	pthread_t		*threads;
	pthread_mutex_t	*forks_id;
	int				*stop;
	// pthread_mutex_t	*exit;
	struct timeval	time_from_start;
	int				i;
}				t_data;

// parsing
int	parsing(t_data *p, int argc, char *argv[]);

// threading
int	thread_init(t_data *p);

// init
int	data_init(t_data *data);
int	philo_init(t_data *data);

// utils
int	custom_usleep(int time_in_ms, t_philo *p);
int	get_time(t_philo *p);

// checking
int	arg_check(int argc);
int	is_integer(char *argv[]);
int	is_number(char *s);
int	is_negative(t_data *data);
int	n_eat_init(int argc, char *argv[], t_data *data);

// libft
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

// free
int	free_data(t_data *data);
int	free_philo(t_philo *p);

#endif