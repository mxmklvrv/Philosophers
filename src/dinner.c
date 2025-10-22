/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:04:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/22 18:53:23 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
}

// eat
// sleep
// think
// write message

bool	write_status(t_philo *philo, char *msg)
{
	size_t	curr_time;

	curr_time = get_time() - philo->table->time_start;
	control_mutex(&philo->table->mtx_msg, LOCK);
	printf("%zu %d %s\n", curr_time, philo->id, msg);
	control_mutex(&philo->table->mtx_msg, UNLOCK);
	return (SUCCESS);
}
