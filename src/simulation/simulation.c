/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:41 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/20 03:07:28 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	simulation(t_config *config)
{
	t_control	*variables;
	int			*is_running;

	if (!create_variables(&variables, &is_running, config))
		return ;
	printf("Somehow, worked\n");
}
