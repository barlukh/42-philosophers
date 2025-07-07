/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/07 13:24:20 by bgazur           ###   ########.fr       */
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
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %zu has started. Left fork: %p, Right fork: %p\n",
		get_time_diff(philo->data), philo->id, philo->fork_left, philo->fork_right);
	pthread_mutex_unlock(&(philo->data->lock));
	return (NULL);
}
