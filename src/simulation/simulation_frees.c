/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 02:27:59 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/03 21:54:08 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_monitor(t_monitor *monitor)
{
	int	index;

	if (monitor->dongles)
		free(monitor->dongles);
	if (monitor->coders_info)
	{
		index = 0;
		while (index < monitor->number_of_coders)
		{
			pthread_mutex_destroy(&monitor->coders_info[index].mutex);
			index++;
		}
		free(monitor->coders_info);
	}
	if (monitor->threads)
		free(monitor->threads);
	free(monitor);
}

void	free_control(t_control *control)
{
	pthread_mutex_destroy(&(control->mutex));
	pthread_mutex_destroy(&(control->mutex_print));
	pthread_cond_destroy(&(control->condition));
	free(control);
}

void	free_heap(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->coders);
	free(heap);
}
