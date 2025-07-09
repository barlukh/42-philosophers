/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:20:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/09 16:53:54 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (i % 2 == 0)
		{
			data->philos[i].fork[0] = &(data->forks[i]);
			data->philos[i].fork[1] = &(data->forks[(i + 1)
					% data->philos_count]);
		}
		else
		{
			data->philos[i].fork[0] = &(data->forks[(i + 1)
					% data->philos_count]);
			data->philos[i].fork[1] = &(data->forks[i]);
		}
		i++;
	}
}

void	set_times(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		data->philos[i].last_meal = get_time();
		i++;
	}
	data->time_start = get_time();
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&(tv), NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000));
}

uint64_t	get_time_diff(uint64_t time)
{
	return (get_time() - time);
}

void	cleanup(t_data *data, int flag)
{
	size_t	i;

	if (flag == CLEAN_ALL)
	{
		pthread_mutex_destroy(&(data->print));
		i = 0;
		while (i < data->forks_created)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
	}
	if (flag == ERR_MTX || flag == CLEAN_ALL)
		free(data->forks);
	if ((flag == ERR_MEM || flag == ERR_MTX || flag == CLEAN_ALL))
		free(data->philos);
}
