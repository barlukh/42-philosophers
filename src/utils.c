/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:20:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/12 12:52:19 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (i % 2 == 0)
		{
			data->philos[i].fork[0] = &(data->forks[i]);
			data->philos[i].fork[1] = &(data->forks[(i + 1)
					% data->philos_count]);
		}
		else
		{
			data->philos[i].fork[0] = &(data->forks[(i + 1)
					% data->philos_count]);
			data->philos[i].fork[1] = &(data->forks[i]);
		}
		i++;
	}
}

void	output_msg(t_philo *philo, const char *s)
{
	if (philo->data->flag_stop != true)
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%ld %zu %s\n",
			get_time_diff(philo->data->time_start), philo->id, s);
		pthread_mutex_unlock(&(philo->data->print));
	}
}

void	output_msg_death(t_philo *philo, const char *s)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu %s\n",
		get_time_diff(philo->data->time_start), philo->id, s);
	pthread_mutex_unlock(&(philo->data->print));
}

void	cleanup(t_data *data, int flag)
{
	size_t	i;

	if (flag == CLEAN_ALL)
	{
		pthread_mutex_destroy(&(data->print));
		i = 0;
		while (i < data->forks_created)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
	}
	if (flag == ERR_MTX || flag == CLEAN_ALL)
		free(data->forks);
	if ((flag == ERR_MEM || flag == ERR_MTX || flag == CLEAN_ALL))
		free(data->philos);
}
