/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:04:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/23 20:23:47 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    if(philo->id % 2 == 0)
        precise_usleep(philo, philo->table->time_to_eat / 2); // for now it half of a time to eat.
    while(dead_man_found(philo) == FAILURE)
    {
        if(take_fork(philo) == FAILURE)
            return (NULL);
        if(eat(philo) == FAILURE)
            return (NULL);
        if(sleep(philo) == FAILURE)
            return (NULL);
        if(think(philo) == FAILURE)
            return (NULL);
    }
    return (NULL);
}
// not sure about delay time tbh
bool    think(t_philo *philo)
{
    size_t time_to_think;
    
    if(write_status(philo, THINKING) == FAILURE)
        return (FAILURE);
    if(philo->table->philo_nbr % 2 != 0)
    {
        time_to_think = philo->table->time_to_eat / 2;
        precise_usleep(philo, time_to_think);
    }
    return (SUCCESS);
}

bool    sleep(t_philo *philo)
{
    if (write_status(philo, SLEEPING) == FAILURE)
        return (FAILURE);
    precise_usleep(philo, philo->table->time_to_sleep);
    return (SUCCESS);
}

bool    eat(t_philo *philo)
{
    if(write_status(philo, EATING) == FAILURE)
    {
        control_mutex(philo->first_fork, UNLOCK);
        control_mutex(philo->second_fork, UNLOCK);
        return (FAILURE);
    }
    control_mutex(&philo->table->mtx_portion, LOCK);
    philo->last_portion_time = get_time();
    philo->portion_count++;
    control_mutex(&philo->table->mtx_portion, UNLOCK);
    precise_usleep(philo, philo->table->time_to_eat);
    control_mutex(philo->first_fork, UNLOCK);
    control_mutex(philo->second_fork, UNLOCK);
    return (SUCCESS);
}

bool    take_fork(t_philo *philo)
{
    control_mutex(philo->first_fork, LOCK);
    if(write_status(philo, FORKING) == FAILURE)
    {
        control_mutex(philo->first_fork, UNLOCK);
        return(FAILURE);
    }
    control_mutex(philo->second_fork, LOCK);
    if(write_status(philo, FORKING) == FAILURE)
    {
        control_mutex(philo->first_fork, UNLOCK);
        control_mutex(philo->second_fork, UNLOCK);
        return(FAILURE);
    }
    return (SUCCESS);
}

bool	write_status(t_philo *philo, char *msg)
{
	size_t	curr_time;

	curr_time = get_time() - philo->table->time_start;
	control_mutex(&philo->table->mtx_msg, LOCK);
    if(philo->table->finita_la_commedia == 1)
    {
        control_mutex(&philo->table->mtx_msg, UNLOCK);
        return (FAILURE);
    }
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

bool sleeping(t_philo *philo)
{
    if(write_status(philo, SLEEPING) == FAILURE)
        return (FAILURE);
    precise_usleep(philo, philo->table->time_to_sleep);
}
