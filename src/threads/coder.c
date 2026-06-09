/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:36:18 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/09 14:45:53 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coder_routine(void *coder_info)
{
	t_coder		*coder;
	t_control	*control;
	int			is_running;

	coder = (t_coder *) coder_info;
	control = coder->control;
	pthread_mutex_lock(&control->mutex);
	control->ready_count++;
	pthread_cond_broadcast(&control->condition);
	while (!control->start)
		pthread_cond_wait(&control->condition, &control->mutex);
	is_running = control->is_running;
	pthread_mutex_unlock(&control->mutex);
	while (is_running)
	{
		coder_work(coder, control);
		pthread_mutex_lock(&control->mutex);
		is_running = control->is_running;
		pthread_mutex_unlock(&control->mutex);
	}
	return (NULL);
}
