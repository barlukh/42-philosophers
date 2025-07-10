/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:41:52 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 10:19:59 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

void	safe_sleep(t_philo *philo, atomic_int time)
{
	uint64_t	sleep_start;

	sleep_start = get_time();
	while (get_time() - sleep_start < time)
	{
		if (philo->data->flag_death == true)
			break ;
		usleep(1000);
	}
}
