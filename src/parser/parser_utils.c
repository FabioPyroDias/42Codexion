/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:36:34 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/01 03:10:17 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	parse_positive_int(char *positive_int)
{
	int	converted_value;

	if (!validate_integer_input(positive_int))
		return (0);
	converted_value = atoi(positive_int);
	if (converted_value <= 0 || strlen(positive_int) > 10)
		return (0);
	return (converted_value);
}

t_schedule	parse_schedule(char *schedule)
{
	if (strcmp(schedule, "fifo") == 0)
		return (FIFO);
	else if (strcmp(schedule, "edf") == 0)
		return (EDF);
	return (INVALID);
}

int	validate_config(t_config *config)
{
	if (config->number_of_coders == 0)
		return (printf("Number of coders invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->time_to_burnout == 0)
		return (printf("Time to burnout invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->time_to_compile == 0)
		return (printf("Time to compile invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->time_to_debug == 0)
		return (printf("Time to debug invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->time_to_refactor == 0)
		return (printf("Time to refactor invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->number_of_compiles_required == 0)
		return (printf("Number of compiles required invalid. "
				"(1 - %d)\n", INT_MAX), 0);
	if (config->dongle_cooldown == 0)
		return (printf("Dongle cooldown invalid. (1 - %d)\n", INT_MAX), 0);
	if (config->scheduler == INVALID)
		return (printf("Scheduler invalid. (fifo/edf)\n"), 0);
	return (1);
}
