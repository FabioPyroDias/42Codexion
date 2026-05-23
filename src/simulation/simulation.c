/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/23 02:45:16 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	simulation(t_config *config)
{
	t_control	**variables;
	int			*is_running;
	pthread_t	thread_monitor;
	pthread_t	thread_dongle;
	int			index;

	if (!create_variables(&variables, &is_running, config))
		return (free_all(config, NULL));
	*is_running = 1;
	if (pthread_create(&thread_monitor, NULL, &monitor_routine, (void *) variables[1]) != 0)
		return (*is_running = 0, free_all(config, variables));
	if (pthread_join(thread_monitor, NULL) != 0)
		return (*is_running = 0, free_all(config, variables));
	index = 0;
	while (index < config->number_of_coders)
	{
		index++;
	}
	/* if (pthread_create(&thread_dongle, NULL, &dongle_routine, (void *) variables[0]) != 0)
		return (*is_running = 0, free_all(config, variables));
	if (pthread_join(thread_dongle, NULL) != 0)
		return (*is_running = 0, free_all(config, variables));
		free_all(config, variables); */
}
