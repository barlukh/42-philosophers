/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:31:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/11 14:53:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_argc(int argc);
static int	convert_argv(int argc, char **argv, t_data *data);
static int	ft_atoi(const char *s);

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (check_argc(argc) != SUCCESS)
	{
		printf(MSG_INV_ARG);
		return (FAILURE);
	}
	if (convert_argv(argc, argv, data) != SUCCESS)
	{
		printf(MSG_INV_ARG);
		return (FAILURE);
	}
	return (SUCCESS);
}

// Checks argument count.
static int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return (FAILURE);
	return (SUCCESS);
}

// Converts arguments in argv into integers.
static int	convert_argv(int argc, char **argv, t_data *data)
{
	data->philos_count = ft_atoi(argv[1]);
	if (data->philos_count == ERROR)
		return (FAILURE);
	data->tt_die = ft_atoi(argv[2]);
	if (data->tt_die == ERROR)
		return (FAILURE);
	data->tt_eat = ft_atoi(argv[3]);
	if (data->tt_eat == ERROR)
		return (FAILURE);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->tt_sleep == ERROR)
		return (FAILURE);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == ERROR)
			return (FAILURE);
	}
	else
		data->must_eat = NOT_SET;
	data->tt_think = (data->tt_die - data->tt_eat - data->tt_sleep) / 2;
	return (SUCCESS);
}

// Converts a string into an integer.
static int	ft_atoi(const char *s)
{
	long long	result;
	size_t		i;

	result = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			return (ERROR);
		i++;
	}
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		result = result * 10 + (s[i] - '0');
		if (result > INT_MAX)
			return (ERROR);
		i++;
	}
	if (s[i] != '\0')
		return (ERROR);
	return ((int)result);
}
