/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/09 16:47:24 by bgazur           ###   ########.fr       */
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
	if (mtx_init(&data) != SUCCESS)
		return (EXIT_FAILURE);
	philos_init(&data);
	if (data.flag_error != ERROR)
		overseer(&data);
	philos_end(&data);
	if (data.flag_error == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
