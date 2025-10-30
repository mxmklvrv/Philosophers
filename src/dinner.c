/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:04:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/30 15:27:29 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// philo routine
// for now it half of a time to eat.
void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		think(philo);
		precise_usleep(philo, philo->table->time_to_eat / 2);
	}
	while (dead_man_found(philo) == FAILURE)
	{
		if (take_fork(philo) == FAILURE)
			return (NULL);
		if (eat(philo) == FAILURE)
			return (NULL);
		if (sleeping(philo) == FAILURE)
			return (NULL);
		if (think(philo) == FAILURE)
			return (NULL);
	}
	return (NULL);
}

bool	think(t_philo *philo)
{
	size_t	time_to_think;

	if (write_status(philo, THINKING) == FAILURE)
		return (FAILURE);
	if (philo->table->philo_nbr % 2 != 0)
	{
		time_to_think = (philo->table->time_to_die - philo->table->time_to_eat
				- philo->table->time_to_sleep) / 2;
		if ((long)time_to_think > 0)
			precise_usleep(philo, time_to_think);
		else
			precise_usleep(philo, 1);
	}
	return (SUCCESS);
}

bool	sleeping(t_philo *philo)
{
	if (write_status(philo, SLEEPING) == FAILURE)
		return (FAILURE);
	precise_usleep(philo, philo->table->time_to_sleep);
	return (SUCCESS);
}

// at what time we should count lst portion time and increase portion limit?
bool	eat(t_philo *philo)
{
	if (write_status(philo, EATING) == FAILURE)
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

bool	take_fork(t_philo *philo)
{
	control_mutex(philo->first_fork, LOCK);
	if (write_status(philo, FORKING) == FAILURE)
	{
		control_mutex(philo->first_fork, UNLOCK);
		return (FAILURE);
	}
	if (philo->table->philo_nbr == 1)
	{
		precise_usleep(philo, philo->table->time_to_die);
		control_mutex(philo->first_fork, UNLOCK);
		return (FAILURE);
	}
	control_mutex(philo->second_fork, LOCK);
	if (write_status(philo, FORKING) == FAILURE)
	{
		control_mutex(philo->first_fork, UNLOCK);
		control_mutex(philo->second_fork, UNLOCK);
		return (FAILURE);
	}
	return (SUCCESS);
}
// mutex death wraps around mutex msg 28.10 update, not tested
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
