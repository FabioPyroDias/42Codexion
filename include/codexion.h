/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:53:46 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/01 04:01:08 by fda-cruz         ###   ########.fr       */
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
	int				error;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
}	t_control;

typedef enum operations
{
	IDLE,
	REQUESTING,
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_operations;

typedef struct s_coder
{
	int				coder_id;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				number_of_compiles_done;
	int				has_left_dongle;
	int				has_right_dongle;
	long			last_compile_time;
	t_operations	current_operation;
	t_control		*control;
}	t_coder;

typedef struct s_dongle
{
	int		occupied;
	int		cooldown_time;
	long	last_release_time;
}	t_dongle;

typedef struct s_monitor
{
	int			number_of_coders;
	t_dongle	*dongles;
	t_coder		*coders_info;
	pthread_t	*threads;
	t_control	*control;
}	t_monitor;

// PARSER METHODS
t_config	*parser(char *argv[]);
int			parse_positive_int(char *positive_int);
t_schedule	parse_schedule(char *schedule);
int			validate_config(t_config *config);

// SIMULATION METHODS
void		simulation(t_config *config);
int		initialize_control(t_control *control, t_config *c);
long		get_current_time();
void		set_coder_config(t_coder *coder, t_config *c, int id, t_control *control);
t_dongle	*populate_dongles(t_config *c);
t_coder		*populate_coders(t_config *c, t_control *control);
pthread_t	*populate_threads(t_config *c);
int			create_variables(t_monitor **monitor, t_control **control, t_config *c);
int			create_threads(t_monitor *monitor, pthread_t *monitor_thread, t_config *c);
int			join_threads(t_monitor *monitor, pthread_t *monitor_thread, t_control *control);
void		free_monitor(t_monitor *monitor);
void		free_control(t_control *control);

// THREADS METHODS
void		*monitor_routine(void *coders_info);
void		*coder_routine(void *coder_info);

// UTILS METHODS
int			validate_integer_input(char *input);