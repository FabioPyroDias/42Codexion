/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 20:07:53 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 18:59:12 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coder_function(void *config)
{
	t_coder	*coder_config;

	coder_config = (t_coder *) config;
	if (coder_config)
		printf("Somehow, I'm - %d - working\n", coder_config->coder_id);
	sleep(rand() % 10 + 3);
	printf("Sou uma thread\n\n");
	return (NULL);
}
