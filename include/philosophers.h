/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:59 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/03 11:12:23 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <stdlib.h>
# include <stdio.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define ERROR -1
# define NOT_SET 0

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/**
 * @brief Data about philosophers and their routine.
 * @param philos Number of philosophers.
 * @param tt_die Time to die.
 * @param tt_eat Time to eat.
 * @param tt_sleep Time to sleep.
 * @param must_eat Number of times each philosopher must eat, 0 if not set.
 */
typedef struct s_data
{
	int	philos;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	must_eat;
}	t_data;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Parses arguments from the command line.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data Data about philosophers and their routine.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int	parse_arguments(int argc, char **argv, t_data *data);

#endif
