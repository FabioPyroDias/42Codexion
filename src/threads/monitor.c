/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:54:51 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 17:13:56 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor_function(void *coder_configs)
{
	t_coder	*coders;

	coders = (t_coder*) coder_configs;
	printf("%p\n", coders);
	return (NULL);
}
