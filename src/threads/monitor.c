/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:10:38 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/03 21:53:29 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor_routine(void *monitor_info)
{
	t_monitor			*monitor;
	t_control			*control;
	t_heap				*heap;

	monitor = (t_monitor *) monitor_info;
	control = monitor->control;
	initialize_heap(&heap, monitor->number_of_coders);
	pthread_mutex_lock(&control->mutex);
	if (!heap)
		control->error = 1;
	control->ready_count++;
	pthread_cond_broadcast(&control->condition);
	while (!control->start)
		pthread_cond_wait(&control->condition, &control->mutex);
	pthread_mutex_unlock(&control->mutex);
	monitor_work(monitor, control, heap);
	free_heap(heap);
	return (NULL);
}
