/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 02:27:59 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/20 15:14:10 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_dongles(t_control **dongles, t_config *c)
{
	t_dongle	**dongle_info;
	int			index;

	if (!dongles || !(*dongles)->data)
		return ;
	dongle_info = ((t_dongle **)(*dongles)->data);
	index = 0;
	while (index < c->number_of_coders)
	{
		if (dongle_info[index])
			free(dongle_info[index]);
		index++;
	}
	free(dongles);
}

void	free_coders(t_control **coders, t_config *c)
{
	t_coder	**coder_info;
	int		index;

	if (!coders || !(*coders)->data)
		return ;
	coder_info = ((t_coder **)(*coders)->data);
	index = 0;
	while (index < c->number_of_coders)
	{
		if (coder_info[index])
			free(coder_info[index]);
		index++;
	}
	free(coders);
}

void	free_threads(t_control **threads)
{
	pthread_t	**thread_info;
	int			index;

	if (!threads || !(*threads)->data)
		return ;
	thread_info = ((pthread_t **)(*threads)->data);
	index = 0;
	while (thread_info[index])
	{
		free(thread_info[index]);
		index++;
	}
	free(threads);
}
