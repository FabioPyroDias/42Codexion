/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:22:27 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	simulation(t_config *config)
{
	t_container	**variables;
	t_control	*control;
	pthread_t	thread_monitor;
	pthread_t	thread_dongle;

	if (!create_variables(&variables, &control, config))
		return (free_all(config, NULL));
	control->start = 0;
	control->is_running = 0;
	control->total_threads = create_threads(variables, &thread_monitor, &thread_dongle);
	if (control->total_threads == config->number_of_coders + 2)
		control->is_running = 1;
	pthread_mutex_lock(&control->mutex);
	while (control->ready_count < control->total_threads)
		pthread_cond_wait(&control->condition, &control->mutex);
	control->start = 1;
	control->start_time = get_current_time();
	pthread_cond_broadcast(&control->condition);
	pthread_mutex_unlock(&control->mutex);
	if (join_threads(variables, &thread_monitor, &thread_dongle, config) == 0)
		control->is_running = 0;
	return (free_control(control), free_all(config, variables));
}
