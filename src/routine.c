/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/09 12:14:40 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	routine_delay(t_philo *philo);
static void	routine_eat(t_philo *philo);
static int	routine_full_check(t_philo *philo);
static void	routine_after_dinner(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	routine_delay(philo);
	while (true)
	{
		routine_eat(philo);
		if (routine_full_check(philo) == true)
			break ;
		routine_after_dinner(philo);
	}
	return (NULL);
}

// Delays the routine to ensure a simultaneous start and to prevent deadlocks.
static void	routine_delay(t_philo *philo)
{
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
	}
	if (philo->id % 2 == 0)
		usleep(DELAY);
}

// Runs the eating routine.
static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_fork_first(philo);
	pthread_mutex_lock(philo->fork[1]);
	output_fork_second(philo);
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
}

// Checks if a philosopher is full.
static int	routine_full_check(t_philo *philo)
{
	if (philo->data->must_eat != NOT_SET)
	{
		philo->times_eaten++;
		if (philo->times_eaten == (size_t)philo->data->must_eat)
			return (true);
	}
	return (false);
}

// Runs the routine for sleeping and thinking.
static void	routine_after_dinner(t_philo *philo)
{
	output_sleeping(philo);
	usleep(philo->data->tt_sleep * 1000);
	output_thinking(philo);
}
