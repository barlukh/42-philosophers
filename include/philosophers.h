/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/04 16:36:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define ERROR 0
# define NO_ERROR 1

# define NOT_SET 0

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/**
 * @brief Atttributes of philosophers and their routine.
 * @param count Number of philosophers.
 * @param tt_die Time to die.
 * @param tt_eat Time to eat.
 * @param tt_sleep Time to sleep.
 * @param must_eat Number of times each philosopher must eat, 0 if not set.
 * @param arr Array of philosophers.
 */
typedef struct s_philo
{
	int			count;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			must_eat;
	pthread_t	*arr;
}	t_philo;

/**
 * @brief Data used by the program.
 * @param err_flag Error flag.
 * @param philo Atttributes of philosophers and their routine.
 */
typedef struct s_data
{
	_Atomic int	err_flag;
	t_philo		philo;
}	t_data;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Parses arguments from the command line.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		parse_arguments(int argc, char **argv, t_data *data);

/**
 * @brief Waits for all philosophers to end their routine.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		philo_end(t_data *data);

/**
 * @brief Creates all philosophers.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		philo_init(t_data *data);

/**
 * @brief 
 * @param arg Data used by the program.
 */
void	*philo_routine(void *arg);

#endif
