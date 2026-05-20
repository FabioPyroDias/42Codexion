/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 02:27:59 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/20 03:06:28 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_coders(t_control **coders)
{
	t_coder	**coder_info;
	int		index;

	if (!coders || !(*coders)->data)
		return ;
	coder_info = (*coders)->data;
	index = 0;
	while (coder_info[index])
	{
		free(coder_info[index]);
		index++;
	}
	free(coders);
}

void	free_threads(t_control **threads)
{
	t_coder	**thread_info;
	int		index;

	if (!threads || !(*threads)->data)
		return ;
	thread_info = (*threads)->data;
	index = 0;
	while (thread_info[index])
	{
		free(thread_info[index]);
		index++;
	}
	free(threads);
}
