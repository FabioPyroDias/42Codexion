/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:18:02 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/25 20:37:50 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	set_coder_config(t_coder *coder, t_config *c, int id, int *is_running)
{
	coder->coder_id = id;
	coder->number_of_coders = c->number_of_coders;
	coder->time_to_burnout = c->time_to_burnout;
	coder->time_to_compile = c->time_to_compile;
	coder->time_to_debug = c->time_to_debug;
	coder->time_to_refactor = c->time_to_refactor;
	coder->number_of_compiles_required = c->number_of_compiles_required;
	coder->number_of_compiles_done = 0;
	coder->is_running = is_running;
}

t_container	*populate_dongles(t_config *c, int *is_running, int *start)
{
	t_container	*dongles_control;
	t_dongle	*dongles;
	int			index;

	dongles_control = malloc(sizeof(t_container));
	if (!dongles_control)
		return (NULL);
	dongles = malloc(sizeof(t_dongle) * c->number_of_coders);
	if (!dongles)
		return (free(dongles_control), NULL);
	index = 0;
	while (index < c->number_of_coders)
	{
		dongles[index].number_of_dongles = c->number_of_coders;
		dongles[index].cooldown_time = c->dongle_cooldown;
		index++;
	}
	dongles_control->data = (void *) dongles;
	dongles_control->is_running = is_running;
	dongles_control->start = start;
	return (dongles_control);
}

t_container	*populate_coders(t_config *c, int *is_running, int *start)
{
	t_container	*coders_control;
	t_coder		*coders;
	int			index;

	coders_control = malloc(sizeof(t_container));
	if (!coders_control)
		return (NULL);
	coders = malloc(sizeof(t_coder) * c->number_of_coders);
	if (!coders)
		return (free(coders_control), NULL);
	index = 0;
	while (index < c->number_of_coders)
	{
		set_coder_config(&coders[index], c, index + 1, is_running);
		coders[index].start = start;
		index++;
	}
	coders_control->data = (void *) coders;
	coders_control->is_running = is_running;
	return (coders_control);
}

t_container	*populate_threads(t_config *c, int *is_running, int *start)
{
	t_container	*threads_control;
	pthread_t	*threads;

	threads_control = malloc(sizeof(t_container));
	if (!threads_control)
		return (NULL);
	threads = malloc(sizeof(pthread_t) * c->number_of_coders);
	if (!threads)
		return (free(threads_control), NULL);
	threads_control->data = (void *) threads;
	threads_control->is_running = is_running;
	threads_control->start = start;
	return (threads_control);
}

int	create_variables(t_container ***variables, int **start, int **is_running, t_config *c)
{
	*is_running = malloc(sizeof(int));
	if (!*is_running)
		return (0);
	*start = malloc(sizeof(int));
	if (!*start)
		return (free(*is_running), 0);
	*variables = malloc(sizeof(t_container *) * 3);
	if (!*variables)
		return (free(*is_running), free(*start), 0);
	(*variables)[0] = populate_dongles(c, *is_running, *start);
	if (!(*variables)[0])
		return (free(*is_running), free(*start), free(*variables), 0);
	(*variables)[1] = populate_coders(c, *is_running, *start);
	if (!(*variables)[1])
		return (free(*is_running), free(*start), free_dongles((*variables)[0]),
			free(*variables), 0);
	(*variables)[2] = populate_threads(c, *is_running, *start);
	if (!(*variables)[2])
		return (free(*is_running), free(*start), free_dongles((*variables)[0]),
			free_coders((*variables)[1]), free(*variables), 0);
	return (1);
}
