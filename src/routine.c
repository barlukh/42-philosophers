/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/13 13:25:30 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*routine_one(t_philo *philo);
static void	routine_delay(t_philo *philo);
static void	routine_eat(t_philo *philo);
static void	routine_sleep_think(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
		else if (philo->data->flag_error == ERROR)
			return (NULL);
		usleep(DELAY_LOOP);
	}
	if (philo->data->philos_count == 1)
		return (routine_one(philo));
	routine_delay(philo);
	while (true)
	{
		routine_eat(philo);
		if (philo->data->flag_stop == true)
			break ;
		routine_sleep_think(philo);
		if (philo->data->flag_stop == true)
			break ;
	}
	return (NULL);
}

// Runs the routine of a single philosopher.
static void	*routine_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_msg(philo, MSG_FORK);
	usleep(philo->data->tt_die * CNVRT);
	pthread_mutex_unlock(philo->fork[0]);
	return (NULL);
}

// Delays the start of all odd philosophers.
static void	routine_delay(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		output_msg(philo, MSG_THINK);
		usleep(philo->data->tt_eat * CNVRT);
	}
}

// Runs the eating routine.
static void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->fork[1]);
	output_msg(philo, MSG_FORK);
	pthread_mutex_lock(&(philo->data->meal));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->data->meal));
	if (philo->data->flag_stop != true)
	{
		output_msg(philo, MSG_EAT);
		safe_sleep(philo, philo->data->tt_eat);
		if (philo->data->must_eat != NOT_SET)
		{
			philo->times_eaten++;
			if (philo->times_eaten == (size_t)philo->data->must_eat)
			{
				philo->data->philos_full++;
				if (philo->data->philos_full == philo->data->philos_count)
					philo->data->flag_stop = true;
			}
		}
	}
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
}

// Runs the sleeping and thinking routine.
static void	routine_sleep_think(t_philo *philo)
{
	output_msg(philo, MSG_SLEEP);
	safe_sleep(philo, philo->data->tt_sleep);
	if (philo->data->flag_stop == true)
		return ;
	output_msg(philo, MSG_THINK);
	if (philo->data->philos_count % 2 != 0)
		safe_sleep(philo, philo->data->tt_think);
}
