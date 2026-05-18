/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   questions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-cruz <fda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:55:58 by fda-cruz          #+#    #+#             */
/*   Updated: 2026/05/18 14:18:10 by fda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

/// @brief 
/// Receiving all the arguments and being one of them "time_to_burnout",
/// leaves the question if an extra validation needs to be taken into
/// consideration when validating the input.
/// "time_to_burnout" starts counting as soon as the thread starts.
/// The only time it resets, it's after the compiling operation is finished.
/// This means there is a whole cycle of "refactoring", "debugging" and, again
/// "compiling" until the "time_to_burnout" is resetted.
/// The question is: should "time_to_burnout" be greater than all the
/// operations time summed together?
/// Example:
/// time_to_burnout = 2000
/// time_to_compile = 1000
/// time_to_debug = 1500
/// time_to_refactor = 1500
/// The operations time reached a total of 4000 while the "time_to_burnout"
/// is only 2000.
/// This means it's impossible for a cycle of operations to be completed
/// before the burnout.
/// @param config 
/// @return
int	extra_parser_validation(t_config *config)
{
	int	total_time;

	total_time = (config->time_to_compile
			+ config->time_to_debug + config->time_to_refactor);
	if (config->time_to_burnout > total_time)
		return (0);
	return (1);
}

/* More Questions:
	- Is another thread needed to update the cooldown timer in each dongle?
*/
