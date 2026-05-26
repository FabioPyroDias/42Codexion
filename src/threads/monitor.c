/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:10:38 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:27:38 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor_routine(void *coders_info)
{
	t_coder		*coders;
	t_control	*control;

	coders = (t_coder *)((t_container *) coders_info)->data;
	control = ((t_container *) coders_info)->control;
	if (control->start)
		control = NULL;
	if (coders->coder_id == 1)
		coders = NULL;
	return (NULL);
}
