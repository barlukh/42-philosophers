/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 09:10:45 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	assign_forks(t_data *data);

int	mem_alloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
	{
		printf("Error allocating memory\n");
		return (FAILURE);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->forks)
	{
		cleanup(data, ERR_MEM);
		printf("Error allocating memory\n");
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
		printf("Error initializing mutex objects\n");
		return (FAILURE);
	}
	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != SUCCESS)
		{
			data->forks_created = i;
			cleanup(data, CLEAN_ALL);
			printf("Error initializing mutex objects\n");
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

	data->flag_error = NOT_SET;
	i = 0;
	while (i < (size_t)data->philos_count)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		assign_forks(data);
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				philo_routine, (void*)&(data->philos[i])) != SUCCESS)
		{
			data->philos_created = i;
			data->flag_error = ERROR;
			printf("Error creating threads\n");
			return ;
		}
		i++;
	}
	data->philos_created = i;
	data->time_start = get_time();
	data->flag_error = NO_ERROR;
}

// Assigns correct fork mutex objects to each philosopher.
static void	assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->philos_count)
	{
		data->philos[i].fork_left = &(data->forks[i]);
		data->philos[i].fork_right = &(data->forks[(i + 1)
				% data->philos_count]);
		i++;
	}
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
			printf("Error joining threads\n");
		}
		i++;
	}
	cleanup(data, CLEAN_ALL);
}
