/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:41:22 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 15:35:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*routine_one(t_philo *philo);
static int	routine_eat(t_philo *philo);
static int	routine_sleep(t_philo *philo);
static int	routine_think(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (true)
	{
		if (philo->data->flag_error == NO_ERROR)
			break ;
	}
	if (philo->id % 2 == 0)
		usleep(DELAY_START);
	output_msg(philo, MSG_THINK);
	if (philo->data->philos_count == 1)
		return (routine_one(philo));
	while (true)
	{
		if (routine_eat(philo) != SUCCESS)
			break ;
		if (routine_sleep(philo) != SUCCESS)
			break ;
		if (routine_think(philo) != SUCCESS)
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
	return (NULL);
}

// Runs the eating routine.
static int	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	output_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->fork[1]);
	output_msg(philo, MSG_FORK);
	output_msg(philo, MSG_EAT);
	philo->last_meal = get_time();
	safe_sleep(philo, philo->data->tt_eat);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
	if (philo->data->must_eat != NOT_SET)
	{
		philo->times_eaten++;
		if (philo->times_eaten == (size_t)philo->data->must_eat)
		{
			philo->data->counter_all_full++;
			return (FAILURE);
		}
	}
	if (philo->data->flag_death == true)
		return (FAILURE);
	return (SUCCESS);
}

// Runs the sleeping routine.
static int	routine_sleep(t_philo *philo)
{
	output_msg(philo, MSG_SLEEP);
	safe_sleep(philo, philo->data->tt_sleep);
	if (philo->data->flag_death == true)
		return (FAILURE);
	return (SUCCESS);
}

// Runs the thinking routine.
static int	routine_think(t_philo *philo)
{
	output_msg(philo, MSG_THINK);
	if (philo->data->philos_count % 2)
		usleep(THINKING);
	if (philo->data->flag_death == true)
		return (FAILURE);
	return (SUCCESS);
}
