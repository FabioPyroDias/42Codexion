/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:36:18 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/24 14:53:57 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coder_routine(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *) coder_info;
	printf("Coder %d: %d\n\n", coder->coder_id, *coder->is_running);
	while(*coder->is_running)
	{
		coder->number_of_compiles_done++;
		printf("Coder %d: %d/%d\n", coder->coder_id, coder->number_of_compiles_done, coder->number_of_compiles_required);
		if (coder->number_of_compiles_done >= coder->number_of_compiles_required)
			return (NULL);
		sleep(coder->coder_id);
	}
	return (NULL);
}
