/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 14:21:10 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/28 17:20:18 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	create_threads(t_monitor *monitor, pthread_t *monitor_thread, t_config *c)
{ //Não sei se t_monitor é apenas um pointer ou tem de ser double pointer
	int	index;
	int	threads_created;

	threads_created = 0;
	if (pthread_create(monitor_thread, NULL, &monitor_routine,
			monitor) != 0) //Não sei se tenho de dar cast -> (void *) *monitor
		return (threads_created);
	threads_created++;
	index = 0;
	while (index < c->number_of_coders)
	{
		if (pthread_create(&((pthread_t *) monitor->threads)[index], NULL,
			&coder_routine, &((t_coder *) monitor->coders_info)[index]) != 0)
			return (threads_created);
		threads_created++;
		index++;
	}
	return (threads_created);
}

int	join_threads(t_monitor *monitor, pthread_t *monitor_thread, t_control *control)
{
	int	result;
	int	index;

	result = 1;
	index = 0;
	if (index < control->total_threads)
	{
		if (pthread_join(*monitor_thread, NULL) != 0)
			result = 0;
	}
	index++;
	while (index < control->total_threads)
	{
		if (pthread_join(((pthread_t *) monitor->threads)[index - 1], NULL) != 0)
			result = 0;
		index++;
	}
	return (result);
}
