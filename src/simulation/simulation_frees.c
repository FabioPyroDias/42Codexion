/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 02:27:59 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/28 17:20:35 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_monitor(t_monitor *monitor)
{
	if (monitor->dongles)
		free(monitor->dongles);
	if (monitor->coders_info)
		free(monitor->coders_info);
	if (monitor->threads)
		free(monitor->threads);
	free(monitor);
}

void	free_control(t_control *control)
{
	pthread_mutex_destroy(&(control->mutex));
	pthread_cond_destroy(&(control->condition));
	free(control);
}
