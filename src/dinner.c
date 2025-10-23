/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:04:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/23 14:08:44 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    if(philo->id % 2 == 0)
        precise_usleep(philo->table->time_to_eat / 2); // for now it half of a time to eat.
    while(dead_man_found(philo) == FAILURE)
    {
        // eat
        // sleep 
        // think
    }
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

bool    dead_man_found(t_philo *philo)
{
    control_mutex(&philo->table->mtx_death, LOCK);
    if(philo->table->finita_la_commedia == 1)
    {
        control_mutex(&philo->table->mtx_death, UNLOCK);
        return (SUCCESS);
    }
    control_mutex(&philo->table->mtx_death, UNLOCK);
    return (FAILURE);
}