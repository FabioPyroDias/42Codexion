/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/24 15:02:49 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	simulation(t_config *config)
{
	t_control	**variables;
	int			*is_running;
	pthread_t	thread_monitor;
	pthread_t	thread_dongle;

	if (!create_variables(&variables, &is_running, config))
		return (free_all(config, NULL));
	*is_running = 0;
	config->threads_created = create_threads(variables, &thread_monitor, &thread_dongle);
	if (config->threads_created == config->number_of_coders + 2)
		*is_running = 1;
	if (join_threads(variables, &thread_monitor, &thread_dongle, config) == 0)
		*is_running = 0;
	free_all(config, variables);
}
