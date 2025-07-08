/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:20:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 09:11:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&(tv), NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000));
}

uint64_t	get_time_diff(t_data *data)
{
	return (get_time() - data->time_start);
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
