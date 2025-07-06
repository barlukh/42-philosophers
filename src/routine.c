/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 11:38:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_data	*data;

	data = arg;
	while (true)
	{
		if (data->flag_error == NO_ERROR)
			break ;
		usleep(3);
	}
	pthread_mutex_lock(&(data->general));
	printf("Routine %ld\n", get_time() - data->time_start);
	pthread_mutex_unlock(&(data->general));
	return (NULL);
}
