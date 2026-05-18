/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:09:51 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/19 00:32:25 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	populate_dongles(t_control **data, int* dongles, int *run)
{
	data = malloc(sizeof(t_control *));
	if (!data)
		return ;
	(*data)->data = dongles;
	(*data)->is_running = run;
}

void	populate_coders(t_control **data, t_coder **cs, t_config *c, int *run)
{
	int		index;

	data = malloc(sizeof(t_control *));
	if (!data)
		return ;
	index = 0;
	while (index < c->number_of_coders)
	{
		cs[index] = malloc(sizeof(t_coder));
		if (!cs[index])
		{
			while (index >= 0)
			{
				index--;
				free(cs[index]);
			}
			free(data);
			return ;
		}
		set_coder_config(cs, c, index + 1);
		index++;
	}
	(*data)->data = cs;
	(*data)->is_running = run;
}

void	populate_threads(t_control **data, t_coder **c, pthread_t **t, int *r)
{
	
}

int	*populate(void **variables, void **container, t_config *c, int *running)
{
	t_control	*control_dongles;
	t_control	*control_coders;
	t_control	*control_threads;

	variables = malloc(sizeof(void **) * 3);
	if (!variables)
		return (0);
	populate_dongles(&control_dongles, container[0], running);
	if (!control_dongles)
		return (free(variables), 0);
	populate_coders(&control_coders, container[1], c, running);
	if (!control_coders)
		return (free(control_coders), free(variables), 0);
	populate_threads(&control_threads, container[2], container[1], running);
	if (!control_threads)
	// This "free(control_coders)" is wrong. I wouldn't free every t_coder inside it, allowing memory leaks. Need fix.
		return (free(control_coders), free(control_dongles),
			free(variables), 0);
	return (1);
}
