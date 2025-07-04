/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:31:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/04 13:43:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_argc(int argc);
static int	convert_argv(int argc, char **argv, t_data *data);
static int	ft_atoi(const char *s);

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (check_argc(argc) == EXIT_FAILURE)
	{
		printf("Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	else if (convert_argv(argc, argv, data) == EXIT_FAILURE)
	{
		printf("Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Checks argument count.
static int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Converts arguments in argv into integers.
static int	convert_argv(int argc, char **argv, t_data *data)
{
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count == ERROR)
		return (EXIT_FAILURE);
	data->tt_die = ft_atoi(argv[2]);
	if (data->tt_die == ERROR)
		return (EXIT_FAILURE);
	data->tt_eat = ft_atoi(argv[3]);
	if (data->tt_eat == ERROR)
		return (EXIT_FAILURE);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->tt_sleep == ERROR)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == ERROR)
			return (EXIT_FAILURE);
	}
	else
		data->must_eat = NOT_SET;
	return (EXIT_SUCCESS);
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
	return ((int)result);
}
