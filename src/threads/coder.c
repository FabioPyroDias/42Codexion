/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:36:18 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/20 03:13:45 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coder(void *container)
{
	t_coder	*coder = (t_coder *) container;
	printf("%d\n\n", coder->coder_id);
	return (NULL);
}
