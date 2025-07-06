/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 12:34:55 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mem_alloc(t_data *data)
{
	data->philo.arr = malloc(sizeof(pthread_t) * data->philo.count);
	if (!data->philo.arr)
	{
		printf("Error allocating memory\n");
		return (FAILURE);
	}
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo.count);
	if (!data->fork)
	{
		cleanup(data, C1);
		printf("Error allocating memory\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	fork_init(t_data *data)
{
	size_t	i;

	if (pthread_mutex_init(&(data->general), NULL) != SUCCESS)
	{
		cleanup(data, C2);
		printf("Error initializing mutex objects\n");
		return (FAILURE);
	}
	i = 0;
	while (i < (size_t)data->philo.count)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL) != SUCCESS)
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

void	philo_init(t_data *data)
{
	size_t	i;

	data->flag_error = NOT_SET;
	i = 0;
	while (i < (size_t)data->philo.count)
	{
		if (pthread_create(&data->philo.arr[i], NULL,
				philo_routine, data) != SUCCESS)
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

void	philo_end(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philos_created)
	{
		if (pthread_join(data->philo.arr[i], NULL) != SUCCESS)
		{
			data->flag_error = ERROR;
			printf("Error joining threads\n");
		}
		i++;
	}
	cleanup(data, C3);
}
