/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:20:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 16:25:40 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&(tv), NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000));
}

uint64_t	get_timestamp(t_data *data)
{
	return (get_time() - data->time_start);
}

void	cleanup(t_data *data, int flag_clean)
{
	size_t	i;

	if (flag_clean == C3)
	{
		pthread_mutex_destroy(&(data->mtx_general));
		i = 0;
		while (i < data->forks_created)
		{
			pthread_mutex_destroy(&(data->mtx_forks[i]));
			i++;
		}
	}
	if (flag_clean == C2 || flag_clean == C3)
		free(data->mtx_forks);
	if ((flag_clean == C1 || flag_clean == C2 || flag_clean == C3))
		free(data->philos);
}
