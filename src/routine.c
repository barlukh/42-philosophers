/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 16:35:10 by bgazur           ###   ########.fr       */
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
	}
	pthread_mutex_lock(&(data->mtx_general));
	printf("Routine %ld: %zu\n", get_timestamp(data), data->philos->id);
	pthread_mutex_unlock(&(data->mtx_general));
	return (NULL);
}
