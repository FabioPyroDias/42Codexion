/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:10:38 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/28 17:23:57 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor_routine(void *coders_info)
{
	t_coder		*coders;

	coders = (t_coder *) coders_info;
	if (coders->coder_id == 1)
		coders = NULL;
	return (NULL);
}
