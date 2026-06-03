/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:14:50 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/03 21:59:42 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	monitor_work(t_monitor *coder, t_control *control, t_heap *heap)
{
	int	is_running;

	pthread_mutex_lock(&control->mutex);
	is_running = control->is_running;
	pthread_mutex_unlock(&control->mutex);
	while (is_running)
	{
		
	}
	return ;
}
