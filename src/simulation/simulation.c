/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 20:09:09 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	set_coder_config(t_coder **coder_config, t_config *config, int id)
{
	(*coder_config)->coder_id = id;
	(*coder_config)->number_of_coders = config->number_of_coders;
	(*coder_config)->time_to_burnout = config->time_to_burnout;
	(*coder_config)->time_to_compile = config->time_to_compile;
	(*coder_config)->time_to_debug = config->time_to_debug;
	(*coder_config)->time_to_refactor = config->time_to_refactor;
	(*coder_config)->number_of_compiles_required = (
			config->number_of_compiles_required);
}

void	**create_environment(t_config *c, int* is_running)
{
	int			*dongles;
	t_coder		**coder_configs;
	pthread_t	*coders;
	void		**container;
	void		**variables;

	container = ft_calloc(sizeof(void**), 3);
	if (!container)
		return (NULL);
	dongles = ft_calloc(sizeof(int), c->number_of_coders + 1);
	if (!dongles)
		return (free(container), NULL);
	coder_configs = ft_calloc(sizeof(t_coder**), c->number_of_coders + 1);
	if (!coder_configs)
		return (free(dongles), free(container), NULL);
	coders = ft_calloc(sizeof(pthread_t*), c->number_of_coders + 1);
	if (!coders)
		return (free(dongles), free(coder_configs), free(container), NULL);
	container[0] = dongles;
	container[1] = coder_configs;
	container[2] = coders;
	if (!populate(variables, container, c, is_running))
		return (free(dongles), free(coder_configs),
			free(container), free(coders), NULL);
	return (free(container), variables);
}

void	simulation(t_config *config)
{
	void		**container;
	int			is_running;

	is_running = 1;
	container = create_environment(config, &is_running);
	if (!container)
		return ;

}
