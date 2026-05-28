/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/28 17:20:43 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	simulation(t_config *config)
{
	t_monitor	*monitor;
	t_control	*control;
	pthread_t	thread_monitor;

	if (!create_variables(&monitor, &control, config))
		return (free(config));
	control->start = 0;
	control->is_running = 0;
	control->total_threads = create_threads(monitor, &thread_monitor, config);
	if (control->total_threads == config->number_of_coders + 1)
		control->is_running = 1;
	pthread_mutex_lock(&control->mutex);
	while (control->ready_count < control->total_threads)
		pthread_cond_wait(&control->condition, &control->mutex);
	if (control->error)
		control->is_running = 0;
	control->start = 1;
	control->start_time = get_current_time();
	pthread_cond_broadcast(&control->condition);
	pthread_mutex_unlock(&control->mutex);
	if (join_threads(monitor, &thread_monitor, control) == 0)
		control->is_running = 0;
	return (free_monitor(monitor), free_control(control), free(config));
}
