/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 12:35:40 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != SUCCESS)
		return (EXIT_FAILURE);
	if (mem_alloc(&data) != SUCCESS)
		return (EXIT_FAILURE);
	if (fork_init(&data) != SUCCESS)
		return (EXIT_FAILURE);
	philo_init(&data);
	philo_end(&data);
	if (data.flag_error == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
