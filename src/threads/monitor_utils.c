/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:14:50 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/09 14:45:42 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	check_burnout(t_monitor *monitor, t_control *control)
{
	t_coder	coder;
	int		index;

	index = 0;
	while (index < monitor->number_of_coders)
	{
		pthread_mutex_lock(&monitor->coders_info[index].mutex);
		coder = monitor->coders_info[index];
		if (coder.current_operation != DONE)
		{
			if (get_current_time() - coder.last_compile_time
				>= coder.time_to_burnout)
			{
				pthread_mutex_unlock(&monitor->coders_info[index].mutex);
				print_message(control, coder.coder_id, "burned out");
				pthread_mutex_lock(&control->mutex);
				control->is_running = 0;
				pthread_mutex_unlock(&control->mutex);
				return (1);
			}
		}
		pthread_mutex_unlock(&monitor->coders_info[index].mutex);
		index++;
	}
	return (0);
}

int	check_compiles(t_monitor *monitor, t_control *control)
{
	int		index;
	t_coder	coder;

	index = 0;
	while (index < monitor->number_of_coders)
	{
		pthread_mutex_lock(&monitor->coders_info[index].mutex);
		coder = monitor->coders_info[index];
		pthread_mutex_unlock(&monitor->coders_info[index].mutex);
		if (coder.current_operation != DONE)
			return (0);
		index++;
	}
	pthread_mutex_lock(&control->mutex);
	control->is_running = 0;
	pthread_mutex_unlock(&control->mutex);
	return (1);
}

void	update_dongles(t_monitor *monitor)
{
	int	index;

	index = 0;
	while (index < monitor->number_of_coders)
	{
		if (!(monitor->dongles[index].is_ready
				|| monitor->dongles[index].occupied))
		{
			if (get_current_time() - monitor->dongles[index].last_release_time
				>= monitor->dongles[index].cooldown_time)
				monitor->dongles[index].is_ready = 1;
		}
		index++;
	}
}

void	schedule_dongles(t_heap *heap, t_monitor *m, t_control *control)
{
	update_requests(heap, m, control);
	release_dongles(m, control);
	if (assign_dongles(heap, m, control))
		pthread_cond_broadcast(&control->condition);
}

void	monitor_work(t_monitor *monitor, t_control *control, t_heap *heap)
{
	int	is_running;

	pthread_mutex_lock(&control->mutex);
	is_running = control->is_running;
	pthread_mutex_unlock(&control->mutex);
	while (is_running)
	{
		if (check_burnout(monitor, control))
			break ;
		if (check_compiles(monitor, control))
			break ;
		update_dongles(monitor);
		schedule_dongles(heap, monitor, control);
		pthread_mutex_lock(&control->mutex);
		is_running = control->is_running;
		pthread_mutex_unlock(&control->mutex);
		usleep(500);
	}
	pthread_mutex_lock(&control->mutex);
	pthread_cond_broadcast(&control->condition);
	pthread_mutex_unlock(&control->mutex);
	return ;
}
