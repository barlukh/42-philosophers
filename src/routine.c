/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 10:09:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	routine_delay(t_philo *philo);
static void	routine_dinner(t_philo *philo);
static int	routine_is_full_check(t_philo *philo);
static void	routine_after_dinner(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	routine_delay(philo);
	while (true)
	{
		if (philo->data->flag_death == true)
			break ;
		routine_dinner(philo);
		if (philo->data->flag_death == true)
			break ;
		if (routine_is_full_check(philo) == true)
			break ;
		if (philo->data->flag_death == true)
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
		usleep(DELAY_START);
}

// Runs the eating routine.
static void	routine_dinner(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->fork[1]);
	output_msg(philo, MSG_FORK);
	output_msg(philo, MSG_EAT);
	safe_sleep(philo, philo->data->tt_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
}

// Checks if a philosopher is full.
static int	routine_is_full_check(t_philo *philo)
{
	if (philo->data->must_eat != NOT_SET)
	{
		philo->times_eaten++;
		if (philo->times_eaten == (size_t)philo->data->must_eat)
		{
			philo->data->counter_all_full++;
			return (true);
		}
	}
	return (false);
}

// Runs the routine for sleeping and thinking.
static void	routine_after_dinner(t_philo *philo)
{
	output_msg(philo, MSG_SLEEP);
	safe_sleep(philo, philo->data->tt_sleep);
	output_msg(philo, MSG_THINK);
}
