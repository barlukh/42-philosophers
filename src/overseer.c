/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:44:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/12 15:48:28 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	check_death(t_data *data);

void	overseer(t_data *data)
{
	while (true)
	{
		check_death(data);
		if (data->flag_stop == true)
			break ;
		usleep(DELAY_LOOP);
	}
}

// Checks if a philosopher died from hunger.
static void	check_death(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		pthread_mutex_lock(&(data->meal));
		if (get_time_diff(data->philos[i].last_meal) >= (uint64_t)data->tt_die)
		{
			data->flag_stop = true;
			usleep(DELAY_MSG_DIED);
			output_msg_death(&(data->philos[i]), MSG_DIED);
			pthread_mutex_unlock(&(data->meal));
			return ;
		}
		pthread_mutex_unlock(&(data->meal));
		i++;
	}
}
