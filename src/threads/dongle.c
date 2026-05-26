/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:42:19 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:29:08 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*dongle_routine(void *dongle_info)
{
	t_dongle	*dongles;
	t_control	*control;

	dongles = (t_dongle *)((t_container *) dongle_info)->data;
	control = (t_control *)((t_container *) dongle_info)->control;
	dongles = NULL;
	if (control->is_running)
		control = NULL;
	return (dongles);
}
