/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:18:02 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/06 20:33:30 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	set_coder_config(t_coder *coder, t_config *c, int id, t_control *control)
{
	coder->coder_id = id;
	coder->time_to_burnout = c->time_to_burnout;
	coder->time_to_compile = c->time_to_compile;
	coder->time_to_debug = c->time_to_debug;
	coder->time_to_refactor = c->time_to_refactor;
	coder->number_of_compiles_required = c->number_of_compiles_required;
	coder->number_of_compiles_done = 0;
	coder->request_time = 0;
	coder->has_left_dongle = 0;
	coder->has_right_dongle = 0;
	coder->last_compile_time = 0;
	coder->current_operation = IDLE;
	if (pthread_mutex_init(&(coder->mutex), NULL) != 0)
		return (0);
	coder->control = control;
	return (1);
}

t_dongle	*populate_dongles(t_config *c)
{
	t_dongle	*dongles;
	int			index;

	dongles = malloc(sizeof(t_dongle) * c->number_of_coders);
	if (!dongles)
		return (NULL);
	index = 0;
	while (index < c->number_of_coders)
	{
		dongles[index].is_ready = 1;
		dongles[index].occupied = 0;
		dongles[index].cooldown_time = c->dongle_cooldown;
		dongles[index].last_release_time = 0;
		index++;
	}
	return (dongles);
}

t_coder	*populate_coders(t_config *c, t_control *control)
{
	t_coder		*coders;
	int			index;

	coders = malloc(sizeof(t_coder) * c->number_of_coders);
	if (!coders)
		return (NULL);
	index = 0;
	while (index < c->number_of_coders)
	{
		if (!set_coder_config(&coders[index], c, index + 1, control))
		{
			while (index > 0)
			{
				index--;
				pthread_mutex_destroy(&coders[index].mutex);
			}
			return (free(coders), NULL);
		}
		index++;
	}
	return (coders);
}

pthread_t	*populate_threads(t_config *c)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * c->number_of_coders);
	if (!threads)
		return (NULL);
	return (threads);
}

int	create_variables(t_monitor **monitor, t_control **control, t_config *c)
{
	*monitor = malloc(sizeof(t_monitor));
	if (!*monitor)
		return (0);
	(*monitor)->number_of_coders = c->number_of_coders;
	(*monitor)->dongles = NULL;
	(*monitor)->coders_info = NULL;
	(*monitor)->threads = NULL;
	*control = malloc(sizeof(t_control));
	if (!*control)
		return (free_monitor(*monitor), 0);
	if (!initialize_control(*control, c))
		return (free_monitor(*monitor), free(*control), 0);
	(*monitor)->dongles = populate_dongles(c);
	if (!(*monitor)->dongles)
		return (free_monitor(*monitor), free_control(*control), 0);
	(*monitor)->coders_info = populate_coders(c, *control);
	if (!(*monitor)->coders_info)
		return (free_monitor(*monitor), free_control(*control), 0);
	(*monitor)->threads = populate_threads(c);
	if (!(*monitor)->threads)
		return (free_monitor(*monitor), free_control(*control), 0);
	(*monitor)->control = *control;
	return (1);
}
