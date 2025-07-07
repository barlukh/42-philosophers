/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/07 12:55:20 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
	}
	pthread_mutex_lock(&(philo->data->mtx_general));
	printf("%ld %zu has started\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->mtx_general));
	return (NULL);
}
