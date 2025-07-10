/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 12:53:20 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	routine_delay(t_philo *philo);
static void	routine_eating(t_philo *philo);
static int	routine_is_full_check(t_philo *philo);
static void	routine_sleeping(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	routine_delay(philo);
	while (true)
	{
		if (philo->data->flag_death == true)
			break ;
		routine_eating(philo);
		if (philo->data->flag_death == true)
			break ;
		if (routine_is_full_check(philo) == true)
			break ;
		if (philo->data->flag_death == true)
			break ;
		routine_sleeping(philo);
		if (philo->data->flag_death == true)
			break ;
		output_msg(philo, MSG_THINK);
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
static void	routine_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_msg(philo, MSG_FORK);
	if (philo->data->philos_count == 1)
	{
		usleep(philo->data->tt_die * 1000);
		return ;
	}
	pthread_mutex_lock(philo->fork[1]);
	output_msg(philo, MSG_FORK);
	output_msg(philo, MSG_EAT);
	philo->last_meal = get_time();
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
static void	routine_sleeping(t_philo *philo)
{
	output_msg(philo, MSG_SLEEP);
	safe_sleep(philo, philo->data->tt_sleep);
}
