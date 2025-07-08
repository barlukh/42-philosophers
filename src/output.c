/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 10:15:41 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	output_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	output_fork_second(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	printf("%ld %zu is eating\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	output_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu is sleeping\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}

void	output_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu is thinking\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}
