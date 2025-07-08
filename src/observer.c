/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:44:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 11:58:45 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	observer_monitor(t_data *data)
{
	int		flag_break;
	size_t	i;

	flag_break = false;
	data->flag_death = false;
	data->flag_full = false;
	while (true)
	{
		i = 0;
		while (i < (size_t)data->philos_count)
		{
			if (data->philos[i].times_eaten == (size_t)data->must_eat)
			{
				flag_break = true;
				data->flag_full = true;
				break ;
			}
			i++;
		}
		if (flag_break == true)
			break ;
	}
}
