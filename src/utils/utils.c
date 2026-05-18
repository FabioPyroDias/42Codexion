/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:45:24 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 19:04:15 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	validate_integer_input(char *input)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (input[index] < '0' || input[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*ptr;
	char	*ptr_temp;
	size_t	index;

	if (nmeb <= 0 || size <= 0)
		return (malloc(0));
	if (nmeb / INT_MAX > size)
		return (malloc(0));
	ptr = malloc(size * nmeb);
	if (!ptr)
		return (NULL);
	ptr_temp = (char *)ptr;
	index = 0;
	while (index < size * nmeb)
	{
		ptr_temp[index] = 0;
		index++;
	}
	return (ptr);
}

void	free_all(void *config)
{
	if (config)
		free(config);
}
