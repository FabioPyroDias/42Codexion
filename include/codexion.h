/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:53:46 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/16 21:33:43 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

typedef enum schedule
{
	FIFO,
	EDF,
	INVALID
}	t_schedule;

typedef struct s_configs
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_schedule		scheduler;
}	t_config;

// PARSER METHODS
t_config	*parser(char *argv[]);
int			parse_positive_int(char *positive_int);
t_schedule	parse_schedule(char *schedule);
int			validate_config(t_config *config);

// UTILS METHODS
void		free_all(void *config);