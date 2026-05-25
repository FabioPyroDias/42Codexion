/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:42:19 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/25 20:37:51 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*dongle_routine(void *dongle_info)
{
	t_dongle	*dongles;
	int			*is_running;

	dongles = (t_dongle *)((t_container *) dongle_info)->data;
	is_running = (int *)((t_container *) dongle_info)->is_running;
	dongles = NULL;
	printf("I AM DONGLES\n");
	while(*is_running)
	{
		printf("I am dongle routine\n");
		sleep(2);
	}
	printf("I am here\n");
	return (dongles);
}
