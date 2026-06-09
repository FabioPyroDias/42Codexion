/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:57:37 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/09 14:19:41 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	set_dongle(t_dongle *dongle, int occupied, int is_ready, int released)
{
	dongle->occupied = occupied;
	dongle->is_ready = is_ready;
	if (released)
		dongle->last_release_time = get_current_time();
}

void	assign_dongle(t_coder *coder, t_monitor *monitor, t_control *control)
{
	pthread_mutex_lock(&control->mutex);
	monitor->coders_info[coder->coder_id - 1].has_left_dongle = 1;
	monitor->coders_info[coder->coder_id - 1].has_right_dongle = 1;
	pthread_mutex_unlock(&control->mutex);
	set_dongle(&monitor->dongles[coder->coder_id - 1], 1, 0, 0);
	set_dongle(&monitor->dongles[coder->coder_id % monitor->number_of_coders],
		1, 0, 0);
	print_message(control, coder->coder_id, "has taken a dongle");
	print_message(control, coder->coder_id, "has taken a dongle");
}

void	update_requests(t_heap *heap, t_monitor *monitor, t_control *control)
{
	int				index;
	t_operations	operation;
	int				has_left_dongle;

	index = 0;
	while (index < monitor->number_of_coders)
	{
		pthread_mutex_lock(&control->mutex);
		has_left_dongle = monitor->coders_info[index].has_left_dongle;
		pthread_mutex_unlock(&control->mutex);
		pthread_mutex_lock(&monitor->coders_info[index].mutex);
		operation = monitor->coders_info[index].current_operation;
		pthread_mutex_unlock(&monitor->coders_info[index].mutex);
		if (operation == REQUESTING && !has_left_dongle)
		{
			if (!heap_contains(heap, &monitor->coders_info[index]))
				heap_push(heap, &monitor->coders_info[index], control);
		}
		index++;
	}
}

void	release_dongles(t_monitor *monitor, t_control *control)
{
	int				i;
	t_operations	op;
	int				has_left_dongle;

	i = 0;
	while (i < monitor->number_of_coders)
	{
		pthread_mutex_lock(&control->mutex);
		has_left_dongle = monitor->coders_info[i].has_left_dongle;
		pthread_mutex_unlock(&control->mutex);
		pthread_mutex_lock(&monitor->coders_info[i].mutex);
		op = monitor->coders_info[i].current_operation;
		pthread_mutex_unlock(&monitor->coders_info[i].mutex);
		if (!(op == REQUESTING || op == COMPILING) && has_left_dongle)
		{
			set_dongle(&monitor->dongles[i], 0, 0, 1);
			set_dongle(&monitor->dongles[(i + 1)
				% monitor->number_of_coders], 0, 0, 1);
			pthread_mutex_lock(&control->mutex);
			monitor->coders_info[i].has_left_dongle = 0;
			monitor->coders_info[i].has_right_dongle = 0;
			pthread_mutex_unlock(&control->mutex);
		}
		i++;
	}
}

int	assign_dongles(t_heap *heap, t_monitor *monitor, t_control *control)
{
	int		in_loop;
	int		to_be_broadcasted;
	t_coder	*coder;

	in_loop = 1;
	to_be_broadcasted = 0;
	while (in_loop)
	{
		if (heap->size == 0)
			return (to_be_broadcasted);
		coder = heap->coders[0];
		if (monitor->dongles[coder->coder_id - 1].is_ready
			&& monitor->dongles[coder->coder_id %
				monitor->number_of_coders].is_ready)
		{
			assign_dongle(coder, monitor, control);
			heap_pop(heap);
			to_be_broadcasted = 1;
		}
		else
			in_loop = 0;
	}
	return (to_be_broadcasted);
}
