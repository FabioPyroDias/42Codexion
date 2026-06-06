/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:53:26 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/04 16:09:16 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	initialize_control(t_control *control, t_config *c)
{
	control->start = 0;
	control->is_running = 0;
	control->ready_count = 0;
	control->total_threads = 0;
	control->start_time = 0;
	control->error = 0;
	if (pthread_mutex_init(&control->mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&control->mutex_print, NULL) != 0)
	{
		pthread_mutex_destroy(&control->mutex);
		return (0);
	}
	if (pthread_cond_init(&control->condition, NULL) != 0)
	{
		pthread_mutex_destroy(&control->mutex);
		pthread_mutex_destroy(&control->mutex_print);
		return (0);
	}
	control->schedule = c->scheduler;
	return (1);
}

void	initialize_heap(t_heap **heap, int capacity)
{
	*heap = malloc(sizeof(t_heap));
	if (!*heap)
		return ;
	(*heap)->coders = malloc(sizeof(t_coder *) * capacity);
	if (!(*heap)->coders)
	{
		free(*heap);
		heap = NULL;
		return ;
	}
	(*heap)->size = 0;
	(*heap)->capacity = capacity;
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_control *control, int id, char *message)
{
	pthread_mutex_lock(&control->mutex_print);
	printf("%ld %d %s\n", get_current_time() - control->start_time,
		id, message);
	pthread_mutex_unlock(&control->mutex_print);
}
