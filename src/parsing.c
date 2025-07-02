/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:31:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/02 17:31:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_argc(int argc);

int	parse_arguments(int argc, char **argv)
{
	if (check_argc == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid argument count!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
