/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 14:21:10 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/08 13:52:48 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	create_threads(t_monitor *monitor, pthread_t *monitor_thread, t_config *c)
{
	int	index;
	int	threads_created;

	threads_created = 0;
	if (pthread_create(monitor_thread, NULL, &monitor_routine,
			monitor) != 0)
		return (threads_created);
	threads_created++;
	index = 0;
	while (index < c->number_of_coders)
	{
		if (pthread_create(&(monitor->threads)[index], NULL,
			&coder_routine, &(monitor->coders_info)[index]) != 0)
			return (threads_created);
		threads_created++;
		index++;
	}
	return (threads_created);
}

int	join_threads(t_monitor *monitor, pthread_t *thread, t_control *control)
{
	int	result;
	int	index;

	result = 1;
	index = 0;
	if (index < control->total_threads)
	{
		if (pthread_join(*thread, NULL) != 0)
			result = 0;
	}
	index++;
	while (index < control->total_threads)
	{
		if (pthread_join(((pthread_t *) monitor->threads)[index - 1],
			NULL) != 0)
			result = 0;
		index++;
	}
	return (result);
}
