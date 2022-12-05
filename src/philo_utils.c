/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/05 16:46:33 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	custom_usleep(int time_in_ms, t_philo *p)
{
	int	start;
	int	now;

	start = get_time(p);
	now = 0;
	while ((now - start) < time_in_ms)
	{
		usleep(50);
		now = get_time(p);
		if (*p->data->stop == 1)
			return (0);
	}
	return (1);
}

int	get_time(t_philo *p)
{
	suseconds_t	n;
	time_t		sec;

	gettimeofday(&p->time.time_now, NULL);
	if (p->time.time_from_start->tv_sec == p->time.time_now.tv_sec)
		n = (p->time.time_now.tv_usec
				- p->time.time_from_start->tv_usec) / 1000;
	else
	{
		sec = p->time.time_now.tv_sec - p->time.time_from_start->tv_sec;
		n = (sec * 1000) + ((p->time.time_now.tv_usec
					- p->time.time_from_start->tv_usec) / 1000);
	}
	return (n);
}
