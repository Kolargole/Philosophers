/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/06 00:14:00 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *p)
{
	p->time.time_in_ms = get_time(p);
	if (p->time.time_in_ms - p->time.end_of_meal >= p->data->args.t_die)
	{
		if (*p->data->stop == 1)
			return (0);
		*p->data->stop = 1;
		usleep(1000);
		p->time.time_in_ms = get_time(p);
		printf("%ld %d died\n", p->time.time_in_ms, *p->philo_id);
		return (1);
	}
	return (0);
}

int	do_something(char something, t_philo *p)
{
	if (*p->data->stop == 1)
		return (0);
	p->time.time_in_ms = get_time(p);
	if (something == 'f')
		printf("%ld %d has taken a fork\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'e')
	{
		printf("%ld %d is eating\n", p->time.time_in_ms, *p->philo_id);
		custom_usleep(p->data->args.t_eat, p);
		p->time.time_in_ms = get_time(p);
		p->time.end_of_meal = p->time.time_in_ms;
	}
	else if (something == 's')
	{
		printf("%ld %d is sleeping\n", p->time.time_in_ms, *p->philo_id);
		custom_usleep(p->data->args.t_sleep, p);
	}
	else if (something == 't')
		printf("%ld %d is thinking\n", p->time.time_in_ms, *p->philo_id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo			*p;

	p = (t_philo *)arg;
	p->time.time_in_ms = get_time(p);
	p->time.end_of_meal = 0;
	if (*p->philo_id % 2 == 0)
		custom_usleep(p->data->args.t_eat, p);
	while (1)
	{
		if (is_dead(p) || *p->n_eat == 0 || *p->data->stop == 1)
			break ;
		pthread_mutex_lock(p->right_fork);
		do_something('f', p);
		pthread_mutex_lock(p->left_fork);
		do_something('f', p);
		do_something('e', p);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		*p->n_eat -= 1;
		if (*p->n_eat == 0)
			break ;
		do_something('s', p);
		do_something('t', p);
	}
	return (0);
}

int	thread_init(t_data *data)
{
	while (data->i < data->args.n_philo)
	{
		if (pthread_create(&data->threads[data->i], NULL,
				&philo_routine, &data->p[data->i]) != 0)
			return (0);
		data->i++;
	}
	data->i = 0;
	while (data->i < data->args.n_philo)
	{
		if (pthread_join(data->threads[data->i], NULL) != 0)
			return (0);
		pthread_mutex_destroy(&data->forks_id[data->i]);
		data->i++;
	}
	return (1);
}
