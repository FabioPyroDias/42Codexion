/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:53:38 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/09 14:30:24 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char *argv[])
{
	t_config	*config;

	if (argc != 9)
		return (printf("ERROR: Expected 8 arguments, "
				"received %d\n", argc - 1), 0);
	config = parser(argv);
	if (!config)
		return (free(config), 0);
	simulation(config);
	return (0);
}
