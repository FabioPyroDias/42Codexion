/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:53:46 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/26 16:24:48 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum schedule
{
	FIFO,
	EDF,
	INVALID
}	t_schedule;

typedef struct s_configs
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_schedule	scheduler;
}	t_config;

typedef struct s_control
{
	int				start;
	int				is_running;
	int				ready_count;
	int				total_threads;
	long			start_time;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
}	t_control;

typedef enum operations
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_operations;

typedef struct s_coder
{
	int				coder_id;
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				number_of_compiles_done;
	t_operations	current_operation;
	t_control		*control;
}	t_coder;

typedef struct s_dongle
{
	int	cooldown_time;
	int	number_of_dongles;
}	t_dongle;

typedef struct s_container
{
	void		*data;
	t_control	*control;
}	t_container;

// PARSER METHODS
t_config	*parser(char *argv[]);
int			parse_positive_int(char *positive_int);
t_schedule	parse_schedule(char *schedule);
int			validate_config(t_config *config);

// SIMULATION METHODS
void		simulation(t_config *config);
int			initialize_control(t_control *control);
long		get_current_time();
void		set_coder_config(t_coder *coder, t_config *c, int id, t_control *control);
t_container	*populate_dongles(t_config *c, t_control *control);
t_container	*populate_coders(t_config *c, t_control *control);
t_container	*populate_threads(t_config *c, t_control *control);
int			create_variables(t_container ***variables, t_control **control, t_config *c);
int	create_threads(t_container **variables, pthread_t *monitor, pthread_t *dongles);
int	join_threads(t_container **variables, pthread_t *monitor, pthread_t *dongles, t_control *control);
void		free_control(t_control *control);
void		free_dongles(t_container *dongles);
void		free_coders(t_container *coders);
void		free_threads(t_container *threads);

// THREADS METHODS
void		*monitor_routine(void *coders_info);
void		*dongle_routine(void *dongle_info);
void		*coder_routine(void *coder_info);

// UTILS METHODS
int			validate_integer_input(char *input);
void		free_all(void *config, t_container **variables);