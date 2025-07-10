/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:57:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/10 08:51:10 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	output_msg(t_philo *philo, const char *s)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %zu %s", get_time_diff(philo->data->time_start), philo->id, s);
	pthread_mutex_unlock(&(philo->data->print));
}
