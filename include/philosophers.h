/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/06 12:46:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define SUCCESS 0
# define FAILURE 1

# define NOT_SET -1
# define ERROR 0
# define NO_ERROR 1

# define C1 1
# define C2 2
# define C3 3
# define C4 4

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
 * @param forks_created Number of succesfully created forks.
 * @param philos_created Number of succesfully created philosophers.
 * @param time_start Starting timestamp.
 * @param general General purpose mutex object.
 * @param fork Array of fork mutex objects.
 * @param philo Atttributes of philosophers and their routine.
 */
typedef struct s_data
{
	_Atomic int		flag_error;
	size_t			forks_created;
	size_t			philos_created;
	uint64_t		time_start;
	pthread_mutex_t	general;
	pthread_mutex_t	*fork;
	t_philo			philo;
}	t_data;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Cleans up resources.
 * @param data Data used by the program.
 * @param flag_clean Flag signaling cleaning operations.
 * @return None.
 */
void		cleanup(t_data *data, int flag_clean);

/**
 * @brief Gets the current time.
 * @param void None.
 * @return Current time.
 */
uint64_t	get_time(void);

/**
 * @brief Gets the current timestamp.
 * @param data Data used by the program.
 * @return Current timestamp.
 */
uint64_t	get_timestamp(t_data *data);

/**
 * @brief Allocates memory for all philosophers and forks.
 * @param data Data used by the program.
 * @return SUCCESS or FAILURE.
 */
int			mem_alloc(t_data *data);

/**
 * @brief Creates all forks.
 * @param data Data used by the program.
 * @return SUCCESS or FAILURE.
 */
int			fork_init(t_data *data);

/**
 * @brief Parses arguments from the command line.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data Data used by the program.
 * @return SUCCESS or FAILURE.
 */
int			parse_arguments(int argc, char **argv, t_data *data);

/**
 * @brief Waits for all philosophers to end their routine.
 * @param data Data used by the program.
 * @return None.
 */
void		philo_end(t_data *data);

/**
 * @brief Creates all philosophers.
 * @param data Data used by the program.
 * @return None.
 */
void		philo_init(t_data *data);

/**
 * @brief Runs each philosopher's routine.
 * @param arg Data used by the program.
 * @return None.
 */
void		*philo_routine(void *arg);

#endif
