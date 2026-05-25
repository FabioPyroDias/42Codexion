/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:10:38 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/25 20:37:50 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor_routine(void *coders_info)
{
	t_coder		*coders;
	int			*is_running;
	int			finished_count;
	int			index;

	coders = (t_coder *)((t_container *) coders_info)->data;
	is_running = ((t_container *) coders_info)->is_running;
	while (*is_running)
	{
		finished_count = 0;
		index = 0;
		while (index < coders[0].number_of_coders)
		{
			if (coders[index].current_time_to_burnout <= 0)
				return (*is_running = 0, NULL);
			if (coders[index].number_of_compiles_done >= coders[index].number_of_compiles_required)
				finished_count++;
			index++;
		}
		if (finished_count == coders[0].number_of_coders)
			return (*is_running = 0, NULL);
		usleep(1);
	}
	return (*is_running = 0, NULL);
}
