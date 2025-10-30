/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:14:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/30 20:16:25 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	write_status(t_philo *philo, char *msg)
{
	size_t	curr_time;

	control_mutex(&philo->table->mtx_death, LOCK);
	if (philo->table->finita_la_commedia == 1)
	{
		control_mutex(&philo->table->mtx_death, UNLOCK);
		return (FAILURE);
	}
	control_mutex(&philo->table->mtx_msg, LOCK);
	curr_time = get_time() - philo->table->time_start;
	printf("%zu %d %s\n", curr_time, philo->id, msg);
	control_mutex(&philo->table->mtx_msg, UNLOCK);
	control_mutex(&philo->table->mtx_death, UNLOCK);
	return (SUCCESS);
}

bool	dead_man_found(t_philo *philo)
{
	control_mutex(&philo->table->mtx_death, LOCK);
	if (philo->table->finita_la_commedia == 1)
	{
		control_mutex(&philo->table->mtx_death, UNLOCK);
		return (SUCCESS);
	}
	control_mutex(&philo->table->mtx_death, UNLOCK);
	return (FAILURE);
}
