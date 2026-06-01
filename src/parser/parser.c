/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:24:07 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/31 20:06:36 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_config	*parser(char *argv[])
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->number_of_coders = parse_positive_int(argv[1]);
	config->time_to_burnout = parse_positive_int(argv[2]);
	config->time_to_compile = parse_positive_int(argv[3]);
	config->time_to_debug = parse_positive_int(argv[4]);
	config->time_to_refactor = parse_positive_int(argv[5]);
	config->number_of_compiles_required = parse_positive_int(argv[6]);
	config->dongle_cooldown = parse_positive_int(argv[7]);
	config->scheduler = parse_schedule(argv[8]);
	if (!validate_config(config))
		return (free(config), NULL);
	return (config);
}
