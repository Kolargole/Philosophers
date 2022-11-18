/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/18 19:34:43 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parsing(t_data *data, int argc, char *argv[])
{
	if (!arg_check(argc)
		|| !is_integer(argv)
		|| !n_eat_init(argc, argv, data))
		return (0);
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->n_philo < 1)
	{
		write(1, "there must be at least one philosopher\n", 39);
		return (0);
	}
	if (!is_negative(data))
		return (0);
	return (1);
}
