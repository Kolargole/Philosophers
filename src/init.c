/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/14 18:13:57 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	fork_init(t_data *data, int i)
{
	data->p[i].left_fork = &data->forks_id[i];
	if (pthread_mutex_init(data->p[i].left_fork, NULL) != 0)
		return (0);
	if (data->args.n_philo > 1)
	{
		if (i < data->args.n_philo - 1)
		{
			data->p[i].right_fork = &data->forks_id[i + 1];
			if (pthread_mutex_init(data->p[i].right_fork, NULL) != 0)
				return (0);
		}
		else
		{
			data->p[i].right_fork = &data->forks_id[0];
			if (pthread_mutex_init(data->p[i].right_fork, NULL) != 0)
				return (0);
		}
	}
	else
		data->p[i].right_fork = NULL;
	return (1);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		if (!fork_init(data, i))
			return (0);
		data->p[i].philo_id = malloc(sizeof(int));
		data->p[i].n_eat = malloc(sizeof(int));
		if (data->p[i].philo_id == NULL
			|| data->p[i].n_eat == NULL)
		{
			free_philo(&data->p[i]);
			return (0);
		}
		data->p[i].data = data;
		*data->p[i].philo_id = i + 1;
		*data->p[i].n_eat = data->args.n_eat;
		i++;
	}
	return (1);
}

int	data_init(t_data *data)
{
	data->p = malloc(data->args.n_philo * sizeof(t_philo));
	data->threads = malloc(data->args.n_philo * sizeof(pthread_t));
	data->forks_id = malloc(data->args.n_philo * sizeof(pthread_mutex_t));
	data->time = malloc(data->args.n_philo * sizeof(t_time));
	data->message_queue = malloc(sizeof(pthread_mutex_t));
	data->death = malloc(sizeof(int));
	if (data->p == NULL
		|| data->threads == NULL
		|| data->forks_id == NULL
		|| data->time == NULL
		|| data->message_queue == NULL
		|| data->death == NULL
		|| pthread_mutex_init(data->message_queue, NULL) != 0)
	{
		free_data(data);
		return (0);
	}
	*data->death = 0;
	if (!philo_init(data))
	{
		free_data(data);
		return (0);
	}
	gettimeofday(&data->time_from_start, NULL);
	return (1);
}
