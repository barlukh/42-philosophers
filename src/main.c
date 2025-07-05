/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/05 13:29:48 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo_alloc(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (mutex_init(&data) == EXIT_FAILURE)
	{
		free(data.philo.arr);
		return (EXIT_FAILURE);
	}
	if (philo_init(&data) == EXIT_FAILURE)
		data.flag_error = ERROR;
	else
		data.flag_error = NO_ERROR;
	return (philo_end(&data));
}
