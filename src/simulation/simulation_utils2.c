/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:53:26 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:14:59 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	initialize_control(t_control *control)
{
	control->start = 0;
	control->is_running = 0;
	control->ready_count = 0;
	control->total_threads = 0;
	control->start_time = 0;
	if (pthread_mutex_init(&(control->mutex), NULL) != 0)
		return (0);
	if (pthread_cond_init(&(control->condition), NULL) != 0)
	{
		pthread_mutex_destroy(&(control->mutex));
		return (0);
	}
	return (1);
}

long	get_current_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
