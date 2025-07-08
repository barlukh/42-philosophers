/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/08 09:11:01 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

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

# define VALID_USLEEP 999

# define SUCCESS 0
# define FAILURE 1

# define NOT_SET -1
# define ERROR 0
# define NO_ERROR 1

# define ERR_MEM 1
# define ERR_MTX 2
# define CLEAN_ALL 3

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

struct					s_philo;
typedef struct s_philo	t_philo;

/**
 * @brief Data used by the program.
 * @param flag_error Flag singaling an error.
 * @param philos_count Number of philosophers.
 * @param tt_die Time to die (milliseconds).
 * @param tt_eat Time to eat (milliseconds).
 * @param tt_sleep Time to sleep (milliseconds).
 * @param must_eat Number of times each philosopher must eat, -1 if not set.
 * @param forks_created Number of successfully created forks.
 * @param philos_created Number of successfully created philosophers.
 * @param time_start Starting time.
 * @param print Mutex object for printf() function.
 * @param forks Array of fork mutex objects.
 * @param philos Array of philosophers and their attributes.
 */
typedef struct s_data
{
	_Atomic int		flag_error;
	int				philos_count;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				must_eat;
	size_t			forks_created;
	size_t			philos_created;
	uint64_t		time_start;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/**
 * @brief Unique attributes of each philosopher.
 * @param id Identification number of a philosopher.
 * @param philo_thread Thread identifier.
 * @param fork_left Mutex object of the left fork.
 * @param fork_right Mutex object of the right fork.
 * @param data Data used by the program.
 */
typedef struct s_philo
{
	size_t			id;
	pthread_t		philo_thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
}	t_philo;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Cleans up resources.
 * @param data Data used by the program.
 * @param flag Flag signaling cleaning operations.
 * @return None.
 */
void		cleanup(t_data *data, int flag);

/**
 * @brief Gets the current time.
 * @param void None.
 * @return Current time (milliseconds).
 */
uint64_t	get_time(void);

/**
 * @brief Gets the difference between the current and starting time.
 * @param data Data used by the program.
 * @return Time difference (milliseconds).
 */
uint64_t	get_time_diff(t_data *data);

/**
 * @brief Allocates memory for all philosophers and forks.
 * @param data Data used by the program.
 * @return SUCCESS or FAILURE.
 */
int			mem_alloc(t_data *data);

/**
 * @brief Initializes all mutex objects.
 * @param data Data used by the program.
 * @return SUCCESS or FAILURE.
 */
int			mtx_init(t_data *data);

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
void		philos_end(t_data *data);

/**
 * @brief Creates all philosophers.
 * @param data Data used by the program.
 * @return None.
 */
void		philos_init(t_data *data);

/**
 * @brief Runs each philosopher's routine.
 * @param arg Data used by the program.
 * @return None.
 */
void		*philo_routine(void *arg);

#endif
