/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 09:11:07 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	routine_forks_even(t_philo *philo);
static void	routine_forks_odd(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
	}
	if (philo->id % 2 != 0)
		usleep(250);
	while (true)
	{
		if (philo->id % 2 != 0)
			routine_forks_odd(philo);
		else
			routine_forks_even(philo);
	}
	return (NULL);
}

static void	routine_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	printf("%ld %zu is eating\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	routine_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu has taken a fork\n", get_time_diff(philo->data), philo->id);
	printf("%ld %zu is eating\n", get_time_diff(philo->data), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}
