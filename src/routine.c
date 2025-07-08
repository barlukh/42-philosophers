/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 10:24:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	routine_delay(t_philo *philo);
static void	routine_eat_even(t_philo *philo);
static void	routine_eat_odd(t_philo *philo);
static void	routine_after_dinner(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	routine_delay(philo);
	while (true)
	{
		if (philo->id % 2 != 0)
			routine_eat_odd(philo);
		else
			routine_eat_even(philo);
		routine_after_dinner(philo);
	}
	return (NULL);
}

static void	routine_delay(t_philo *philo)
{
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
	}
	if (philo->id % 2 != 0)
		usleep(DELAY);
}

static void	routine_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	output_fork_first(philo);
	pthread_mutex_lock(philo->fork_right);
	output_fork_second(philo);
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	routine_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	output_fork_first(philo);
	pthread_mutex_lock(philo->fork_left);
	output_fork_second(philo);
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

static void	routine_after_dinner(t_philo *philo)
{
	output_sleeping(philo);
	usleep(philo->data->tt_sleep * 1000);
	output_thinking(philo);
}
