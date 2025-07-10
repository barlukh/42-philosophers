/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 09:13:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mem_alloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
	{
		printf(MSG_ERR_MEM);
		return (FAILURE);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->forks)
	{
		cleanup(data, ERR_MEM);
		printf(MSG_ERR_MEM);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	mtx_init(t_data *data)
{
	size_t	i;

	if (pthread_mutex_init(&(data->print), NULL) != SUCCESS)
	{
		cleanup(data, ERR_MTX);
		printf(MSG_ERR_INIT);
		return (FAILURE);
	}
	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != SUCCESS)
		{
			data->forks_created = i;
			cleanup(data, CLEAN_ALL);
			printf(MSG_ERR_INIT);
			return (FAILURE);
		}
		i++;
	}
	data->forks_created = i;
	return (SUCCESS);
}

void	philos_init(t_data *data)
{
	size_t	i;

	assign_forks(data);
	data->flag_error = NOT_SET;
	data->flag_death = false;
	data->counter_all_full = 0;
	i = 0;
	while (i < (size_t)data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				philo_routine, (void*)&(data->philos[i])) != SUCCESS)
		{
			data->philos_created = i;
			data->flag_error = ERROR;
			printf(MSG_ERR_CREATE);
			return ;
		}
		i++;
	}
	data->philos_created = i;
	set_times(data);
	data->flag_error = NO_ERROR;
}

void	philos_end(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philos_created)
	{
		if (pthread_join(data->philos[i].philo_thread, NULL) != SUCCESS)
		{
			data->flag_error = ERROR;
			printf(MSG_ERR_JOIN);
		}
		i++;
	}
	cleanup(data, CLEAN_ALL);
}
