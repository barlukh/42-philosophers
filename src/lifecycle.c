/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/07 11:50:35 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mem_alloc(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
	{
		printf("Error allocating memory\n");
		return (FAILURE);
	}
	data->mtx_forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->mtx_forks)
	{
		cleanup(data, C1);
		printf("Error allocating memory\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	forks_init(t_data *data)
{
	size_t	i;

	if (pthread_mutex_init(&(data->mtx_general), NULL) != SUCCESS)
	{
		cleanup(data, C2);
		printf("Error initializing mutex objects\n");
		return (FAILURE);
	}
	i = 0;
	while (i < (size_t)data->philos_count)
	{
		if (pthread_mutex_init(&(data->mtx_forks[i]), NULL) != SUCCESS)
		{
			data->forks_created = i;
			cleanup(data, C3);
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
	cleanup(data, C3);
}
