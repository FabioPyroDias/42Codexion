/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 23:34:02 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/03 16:48:23 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/codexion.h"

void	coder_request(t_coder *coder, t_control *control)
{
	pthread_mutex_lock(&coder->mutex);
	coder->current_operation = REQUESTING;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&control->mutex);
	while (!(coder->has_left_dongle && coder->has_right_dongle))
	{
		if (!control->is_running)
		{
			pthread_mutex_unlock(&control->mutex);
			return ;
		}
		pthread_cond_wait(&control->condition, &control->mutex);
	}
	pthread_mutex_unlock(&control->mutex);
	pthread_mutex_lock(&coder->mutex);
	coder->current_operation = COMPILING;
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_compile(t_coder *coder, t_control *control)
{
	long	compile_time;

	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_time = get_current_time();
	compile_time = coder->last_compile_time + coder->time_to_compile;
	pthread_mutex_unlock(&coder->mutex);
	while (get_current_time() < compile_time)
	{
		pthread_mutex_lock(&control->mutex);
		if (!control->is_running)
			return (pthread_mutex_unlock(&control->mutex), (void) 0);
		pthread_mutex_unlock(&control->mutex);
		usleep(1000);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->number_of_compiles_done++;
	if (coder->number_of_compiles_done >= coder->number_of_compiles_required)
	{
		coder->current_operation = DONE;
		pthread_mutex_unlock(&coder->mutex);
		return ;
	}
	coder->current_operation = DEBUGGING;
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_debug(t_coder *coder, t_control *control)
{
	long	debug_time;

	pthread_mutex_lock(&coder->mutex);
	debug_time = get_current_time() + coder->time_to_debug;
	pthread_mutex_unlock(&coder->mutex);
	while (get_current_time() < debug_time)
	{
		pthread_mutex_lock(&control->mutex);
		if (!control->is_running)
		{
			pthread_mutex_unlock(&control->mutex);
			return;
		}
		pthread_mutex_unlock(&control->mutex);
		usleep(1000);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->current_operation = REFACTORING;
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_refactor(t_coder *coder, t_control *control)
{
	long	refactor_time;

	pthread_mutex_lock(&coder->mutex);
	refactor_time = get_current_time() + coder->time_to_refactor;
	pthread_mutex_unlock(&coder->mutex);
	while (get_current_time() < refactor_time)
	{
		pthread_mutex_lock(&control->mutex);
		if (!control->is_running)
		{
			pthread_mutex_unlock(&control->mutex);
			return;
		}
		pthread_mutex_unlock(&control->mutex);
		usleep(1000);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->current_operation = REQUESTING;
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_work(t_coder *coder, t_control *control)
{
	t_operations	current_operation;

	pthread_mutex_lock(&coder->mutex);
	current_operation = coder->current_operation;
	pthread_mutex_unlock(&coder->mutex);
	if (current_operation == DONE)
		return ;
	else if (current_operation == IDLE || current_operation == REQUESTING)
		coder_request(coder, control);
	else if (current_operation == COMPILING)
	{
		print_message(control, coder->coder_id, "is compiling");
		coder_compile(coder, control);
	}
	else if (current_operation == DEBUGGING)
	{
		print_message(control, coder->coder_id, "is debugging");
		coder_debug(coder, control);
	}
	else if (current_operation == REFACTORING)
	{
		print_message(control, coder->coder_id, "is refactoring");
		coder_refactor(coder, control);
	}
}
