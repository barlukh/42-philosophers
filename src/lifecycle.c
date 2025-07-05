/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/05 14:49:03 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_alloc(t_data *data)
{
	data->philo.arr = malloc(sizeof(pthread_t) * data->philo.count);
	if (!data->philo.arr)
	{
		printf("Error allocating memory\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	philo_init(t_data *data)
{
	size_t	i;

	data->flag_error = NOT_SET;
	i = 0;
	while (i < (size_t)data->philo.count)
	{
		if (pthread_create(&data->philo.arr[i], NULL,
				philo_routine, data) != EXIT_SUCCESS)
		{
			printf("Error creating thread (index %zu)\n", i);
			data->philos_created = i;
			return (EXIT_FAILURE);
		}
		i++;
	}
	data->philos_created = i;
	return (EXIT_SUCCESS);
}

int	philo_end(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philos_created)
	{
		if (pthread_join(data->philo.arr[i], NULL) != EXIT_SUCCESS)
		{
			printf("Error joining thread (index %zu)\n", i);
			data->flag_error = ERROR;
		}
		i++;
	}
	free(data->philo.arr);
	if (mutex_destroy(data) == EXIT_FAILURE)
		data->flag_error = ERROR;
	if (data->flag_error == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
