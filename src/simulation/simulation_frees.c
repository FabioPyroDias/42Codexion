/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 02:27:59 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/25 20:37:51 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_dongles(t_container *dongles)
{
	free(dongles->data);
	free(dongles);
}

void	free_coders(t_container *coders)
{
	free(coders->data);
	free(coders);
}

void	free_threads(t_container *threads)
{
	free(threads->data);
	free(threads);
}
