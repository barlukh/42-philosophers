/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:44:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/09 17:17:29 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	check_death(t_data *data);

void	overseer(t_data *data)
{
	while (true)
	{
		check_death(data);
		if (data->flag_death == true)
			break ;
		if (data->flag_all_full == data->philos_count)
			break ;
	}
}

// Checks if a philosopher died from hunger.
static void	check_death(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (get_time_diff(data->philos[i].last_meal) >= data->tt_die)
		{
			data->flag_death = true;
			usleep(DELAY_DEATH);
			output_death(&(data->philos[i]));
			return ;
		}
		i++;
	}
	return ;
}
