/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/04 17:19:07 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_init(t_data *data)
{
	size_t	i;

	data->philo.arr = malloc(sizeof(pthread_t) * data->philo.count);
	if (!data->philo.arr)
	{
		printf("Error allocating memory\n");
		return (EXIT_FAILURE);
	}
	data->err_flag = NO_ERROR;
	i = 0;
	while (i < (size_t)data->philo.count)
	{
		if (pthread_create(&data->philo.arr[i], NULL, philo_routine, data) != 0)
		{
			printf("Error creating thread number %lu\n", data->philo.arr[i]);
			data->err_flag = ERROR;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philo_end(t_data *data)
{
	size_t	i;

	data->err_flag = NO_ERROR;
	i = 0;
	while (i < (size_t)data->philo.count)
	{
		if (pthread_join(data->philo.arr[i], NULL) != 0)
		{
			data->err_flag = ERROR;
			printf("Error joining thread number %lu\n", data->philo.arr[i]);
		}
		i++;
	}
	free(data->philo.arr);
	if (data->err_flag == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
