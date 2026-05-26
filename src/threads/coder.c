/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:36:18 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:29:53 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coder_routine(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *) coder_info;
	if (coder->control->start)
		coder = NULL;
	return (NULL);
}
