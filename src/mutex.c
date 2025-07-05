/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:05:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/05 13:32:07 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mutex_init(t_data *data)
{
	if (pthread_mutex_init(&(data->lock), NULL) != EXIT_SUCCESS)
	{
		printf("Error initializing mutex object\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	mutex_destroy(t_data *data)
{
	if (pthread_mutex_destroy(&(data->lock)) != EXIT_SUCCESS)
	{
		printf("Error destroying mutex object\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
