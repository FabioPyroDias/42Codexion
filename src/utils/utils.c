/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:24 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/25 20:37:50 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	validate_integer_input(char *input)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (input[index] < '0' || input[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

void	free_all(void *config, t_container **variables)
{
	if (config)
		free(config);
	if (variables)
	{
		free(variables[0]->is_running);
		free_dongles(variables[0]);
		free_coders(variables[1]);
		free_threads(variables[2]);
		free(variables);
	}
}
