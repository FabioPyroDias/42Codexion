/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:18:02 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/20 03:14:20 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	set_coder_config(t_coder *coder, t_config *c, int id)
{
	coder->coder_id = id;
	coder->number_of_coders = c->number_of_coders;
	coder->time_to_burnout = c->time_to_burnout;
	coder->time_to_compile = c->time_to_compile;
	coder->time_to_debug = c->time_to_debug;
	coder->time_to_refactor = c->time_to_refactor;
	coder->number_of_compiles_required = c->number_of_compiles_required;
}

t_control	**populate_dongles(t_config *c, int *is_running)
{
	t_control	**dongles_control;
	int			*dongles;

	dongles_control = malloc(sizeof(t_control*));
	if (!dongles_control)
		return (NULL);
	dongles = ft_calloc(c->number_of_coders + 1, sizeof(int));
	if (!dongles)
		return (free(dongles_control), NULL);
	dongles = memset(dongles, 0, c->number_of_coders);
	(*dongles_control)->data = dongles;
	(*dongles_control)->is_running = is_running;
	return (dongles_control);
}

t_control	**populate_coders(t_config *c, int *is_running)
{
	t_control	**coders_control;
	t_coder		**coders;
	int			index;

	coders_control = malloc(sizeof(t_control*));
	if (!coders_control)
		return (NULL);
	coders = malloc(sizeof(t_coder **) * (c->number_of_coders + 1));
	if (!coders)
		return (free(coders_control), NULL);
	coders[c->number_of_coders] = NULL;
	index = 0;
	while (index < c->number_of_coders)
	{
		coders[index] = malloc(sizeof(t_coder *));
		if (!coders[index])
			return (free_coders(coders_control), NULL);
		set_coder_config(coders[index], c, index + 1);
		index++;
	}
	(*coders_control)->data = coders;
	(*coders_control)->is_running = is_running;
	return (coders_control);
}

t_control	**populate_threads(t_config *c, int *is_running)
{
	t_control	**threads_control;
	pthread_t	**threads;
	int			index;

	threads_control = malloc(sizeof(t_control*));
	if (!threads_control)
		return (NULL);
	threads = malloc(sizeof(pthread_t *) * (c->number_of_coders + 1));
	if (!threads)
		return (free(threads_control), NULL);
	threads[c->number_of_coders] = NULL;
	index = 0;
	while (index < c->number_of_coders)
	{
		threads[index] = malloc(sizeof(t_coder *));
		if (!threads[index])
			return (free_threads(threads_control), NULL);
		index++;
	}
	(*threads_control)->data = threads;
	(*threads_control)->is_running = is_running;
	return (threads_control);
}

int	create_variables(t_control ***variables, int **is_running, t_config *c)
{
	*is_running = malloc(sizeof(int*));
	if (!*is_running)
		return (0);
	**is_running = 0;
	*variables = malloc(sizeof(t_control **) * 3);
	if (!variables)
		return (free(*is_running), 0);
	variables[0] = populate_dongles(c, *is_running);
	if (!variables[0])
		return (free(*is_running), free(*variables), 0);
	variables[1] = populate_coders(c, *is_running);
	if (!variables[1])
		return (free(*is_running), free(variables[0]), free(*variables), 0);
	variables[2] = populate_threads(c, *is_running);
	if (!variables[2])
		return (free(*is_running), free(variables[0]),
			free_coders(variables[1]), 0);
	return (1);
}
