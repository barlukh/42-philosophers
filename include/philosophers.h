/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/05 13:44:33 by bgazur           ###   ########.fr       */
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

# define NOT_SET -1
# define ERROR 0
# define NO_ERROR 1

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/**
 * @brief Atttributes of philosophers and their routine.
 * @param count Number of philosophers.
 * @param tt_die Time to die.
 * @param tt_eat Time to eat.
 * @param tt_sleep Time to sleep.
 * @param must_eat Number of times each philosopher must eat, -1 if not set.
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
 * @param flag_error Flag singaling an error.
 * @param philos_created Number of succesfully created philosophers.
 * @param philo Atttributes of philosophers and their routine.
 */
typedef struct s_data
{
	_Atomic int		flag_error;
	size_t			philos_created;
	pthread_mutex_t	lock;
	t_philo			philo;
}	t_data;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Destroys a mutex object.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		mutex_destroy(t_data *data);

/**
 * @brief Initializes a mutex object.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		mutex_init(t_data *data);

/**
 * @brief Parses arguments from the command line.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		parse_arguments(int argc, char **argv, t_data *data);

/**
 * @brief Allocates memory for all philosophers.
 * @param data Data used by the program.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		philo_alloc(t_data *data);

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
 * @brief Runs each philosopher's routine.
 * @param arg Data used by the program.
 */
void	*philo_routine(void *arg);

#endif
