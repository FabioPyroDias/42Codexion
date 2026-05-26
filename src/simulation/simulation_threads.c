/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 14:21:10 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:24:30 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	create_threads(t_container **variables, pthread_t *monitor,
		pthread_t *dongles)
{
	int	index;
	int	max_coders;
	int	threads_created;

	threads_created = 0;
	if (pthread_create(monitor, NULL, &monitor_routine,
			(void *) variables[1]) != 0)
		return (threads_created);
	threads_created++;
	if (pthread_create(dongles, NULL, &dongle_routine,
			(void *) variables[0]) != 0)
		return (threads_created);
	threads_created++;
	max_coders = ((t_coder *)variables[1]->data)->number_of_coders;
	index = 0;
	while (index < max_coders)
	{
		if (pthread_create(&((pthread_t *)variables[2]->data)[index], NULL,
			&coder_routine, &((t_coder *)variables[1]->data)[index]) != 0)
			return (threads_created);
		threads_created++;
		index++;
	}
	return (threads_created);
}

int	join_threads(t_container **variables, pthread_t *monitor,
		pthread_t *dongles, t_control *control)
{
	int	result;
	int	index;

	result = 1;
	index = 0;
	if (index < control->total_threads)
	{
		if (pthread_join(*monitor, NULL) != 0)
			result = 0;
	}
	index++;
	if (index < control->total_threads)
	{
		if (pthread_join(*dongles, NULL) != 0)
			result = 0;
	}
	index++;
	while (index < control->total_threads)
	{
		if (pthread_join(((pthread_t *) variables[2]->data)[index - 2], NULL) != 0)
			result = 0;
		index++;
	}
	return (result);
}
