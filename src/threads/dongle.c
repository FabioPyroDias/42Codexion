/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:56:48 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 19:06:12 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*dongle_function(void *dongle_config)
{
	int				*dongles;
	int				number_of_dongles;

	dongles = (int *) dongle_config;
	number_of_dongles = 0;
	while (1)
	{
		if (dongles[number_of_dongles] == 0)
			break;
		number_of_dongles++;
	}
	return (NULL);
}
