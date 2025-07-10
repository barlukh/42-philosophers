/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 10:18:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define MSG_INV_ARG "Invalid arguments\n"
# define MSG_ERR_MEM "Error allocating memory\n"
# define MSG_ERR_INIT "Error initializing mutex objects\n"
# define MSG_ERR_CREATE "Error creating threads\n"
# define MSG_ERR_JOIN "Error joining threads\n"

# define MSG_FORK "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"
# define MSG_DIED "died\n"

# define DELAY_START 250
# define DELAY_MSG_DIED 1000

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
 * @param philos_count Number of philosophers.
 * @param tt_die Time to die (milliseconds).
 * @param flag_error Flag singaling an error.
 * @param flag_death Flag signaling a death of a philosopher.
 * @param counter_all_full Counter tracking if all philosophers have eaten.
 * @param tt_eat Time to eat (milliseconds).
 * @param tt_sleep Time to sleep (milliseconds).
 * @param must_eat Number of times each philosopher must eat, -1 if not set.
 * @param forks_created Number of successfully created forks.
 * @param philos_created Number of successfully created philosophers.
 * @param time_start Starting time of the simulation.
 * @param print Mutex object for printf() function.
 * @param forks Array of fork mutex objects.
 * @param philos Array of philosophers and their attributes.
 */
typedef struct s_data
{
	int				philos_count;
	int				tt_die;
	atomic_int		flag_error;
	atomic_int		flag_death;
	atomic_int		counter_all_full;
	atomic_int		tt_eat;
	atomic_int		tt_sleep;
	atomic_int		must_eat;
	size_t			forks_created;
	size_t			philos_created;
	uint64_t		time_start;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/**
 * @brief Unique attributes of each philosopher.
 * @param last_meal Time of the last  meal.
 * @param id Identification number of a philosopher.
 * @param times_eaten Counter of how many times has a philosopher eaten.
 * @param philo_thread Thread identifier.
 * @param fork Array of two fork pointers assigned to a philosopher.
 * @param data Data used by the program.
 */
typedef struct s_philo
{
	_Atomic uint64_t	last_meal;
	size_t				id;
	size_t				times_eaten;
	pthread_t			philo_thread;
	pthread_mutex_t		*fork[2];
	t_data				*data;
}	t_philo;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Assigns fork mutex objects to each philosopher.
 * @param data Data used by the program.
 * @return None.
 */
void		assign_forks(t_data *data);

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
 * @brief Gets the difference between the current and the passed time.
 * @param time Time value to count the difference from.
 * @return Time difference (milliseconds).
 */
uint64_t	get_time_diff(uint64_t time);

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
 * @brief Prints a status change message in a thread safe manner.
 * @param philo Unique attributes of each philosopher.
 * @param s Message to output.
 * @return None.
 */
void		output_msg(t_philo *philo, const char *s);

/**
 * @brief Monitors the death state of each philosopher.
 * @param data Data used by the program.
 */
void		overseer(t_data *data);

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

/**
 * @brief Uses usleep() function in smaller cycles.
 * @param philo Unique attributes of each philosopher.
 * @param time Total amount of time to pass to usleep().
 */
void		safe_sleep(t_philo *philo, atomic_int time);

/**
 * @brief Sets initial times for last meal and simulation start.
 * @param data Data used by the program.
 * @return None.
 */
void		set_times(t_data *data);

#endif
