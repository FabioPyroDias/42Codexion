/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 13:48:14 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/06/07 16:38:33 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	heap_shift_right(t_heap *heap, int stop_index)
{
	int	index;

	index = heap->size;
	while (index > stop_index)
	{
		heap->coders[index] = heap->coders[index - 1];
		index--;
	}
}

void	heap_push(t_heap *heap, t_coder *coder, t_control *control)
{
	int	index;

	if (heap->size == heap->capacity)
		return ;
	index = heap->size;
	while (index > 0)
	{
		index--;
		if (!heap_compare(coder, heap->coders[index], control))
		{
			heap_shift_right(heap, index);
			heap->coders[index + 1] = coder;
			heap->size++;
			return ;
		}
	}
	heap_shift_right(heap, index);
	heap->coders[index] = coder;
	heap->size++;
}

t_coder	*heap_pop(t_heap *heap)
{
	t_coder	*coder;
	int		index;

	if (heap->size == 0)
		return (NULL);
	coder = heap->coders[0];
	index = 0;
	while (index < heap->size - 1)
	{
		heap->coders[index] = heap->coders[index + 1];
		index++;
	}
	heap->size--;
	return (coder);
}

int	heap_contains(t_heap *heap, t_coder *coder)
{
	int	index;

	index = 0;
	while (index < heap->size)
	{
		if (heap->coders[index] == coder)
			return (1);
		index++;
	}
	return (0);
}

int	heap_compare(t_coder *coder1, t_coder *coder2, t_control *control)
{
	if (control->schedule == FIFO)
	{
		if (coder1->request_time < coder2->request_time)
			return (1);
		else if (coder1->request_time > coder2->request_time)
			return (0);
	}
	else
	{
		if (coder1->last_compile_time + coder1->time_to_burnout
			< coder2->last_compile_time + coder2->time_to_burnout)
			return (1);
		else if (coder1->last_compile_time + coder1->time_to_burnout
			> coder2->last_compile_time + coder2->time_to_burnout)
			return (0);
	}
	if (coder1->coder_id < coder2->coder_id)
		return (1);
	return (0);
}
