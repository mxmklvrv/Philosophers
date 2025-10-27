/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:04:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/27 12:08:52 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// philo routine
void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo, philo->table->time_to_eat / 2);
	// for now it half of a time to eat.
	while (dead_man_found(philo) == FAILURE)
	{
		if (take_fork(philo) == FAILURE)
			return (NULL);
		if (eat(philo) == FAILURE)
			return (NULL);
		if (sleep(philo) == FAILURE)
			return (NULL);
		if (think(philo) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
// waiter routin to check if someone is dead or pasta finita
// addded 1ms delay to reduce cpu load 
void	*serving_dinner(void *arg)
{
	t_trattoria	*table;

	table = (t_trattoria *)arg;
	while (69)
	{
		if (tomb_needed(table) == SUCCESS)
			break ;
        if (bill_needed(table) == SUCCESS)
            break;
        usleep(1000);
	}
	return (NULL);
}
// checks if all ate 
bool    bill_needed(t_trattoria *table)
{
    int i;
    int full;

    i = -1;
    full = 0;
    if(table->portion_limit == -1)
        return (FAILURE);
    while(++i < table->philo_nbr)
    {
        control_mutex(&table->mtx_portion, LOCK);
        if(table->philos[i].portion_count >= table->portion_limit)
            full++;
        control_mutex(&table->mtx_portion, UNLOCK);
    }
    if(full == table->philo_nbr)
    {
        control_mutex(&table->mtx_death, LOCK);
        table->finita_la_commedia = 1;
        control_mutex(&table->mtx_death, UNLOCK);
        return (SUCCESS);
    }
    return (FAILURE);
} 

// checks if someone is dead
bool	tomb_needed(t_trattoria *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		control_mutex(&table->mtx_portion, LOCK);
		if (still_alive(table, i) == FAILURE)
			return (control_mutex(&table->mtx_portion, UNLOCK), SUCCESS);
		control_mutex(&table->mtx_portion, UNLOCK);
	}
    return (FAILURE);
}

// checks if the time from the last portion >= death time
bool	still_alive(t_trattoria *table, int i)
{
	size_t	curr_time;

	curr_time = get_time();
	if (curr_time - table->philos[i].last_portion_time >= table->time_to_die)
	{
		write_status(&table->philos[i], DIED);
        control_mutex(&table->mtx_death, LOCK);
		table->finita_la_commedia = 1;
        control_mutex(&table->mtx_death, UNLOCK);
		return (FAILURE);
	}
	return (SUCCESS);
}

// not sure about delay time tbh
bool	think(t_philo *philo)
{
	size_t	time_to_think;

	if (write_status(philo, THINKING) == FAILURE)
		return (FAILURE);
	if (philo->table->philo_nbr % 2 != 0)
	{
		time_to_think = philo->table->time_to_eat / 2;
		precise_usleep(philo, time_to_think);
	}
	return (SUCCESS);
}

bool	sleep(t_philo *philo)
{
	if (write_status(philo, SLEEPING) == FAILURE)
		return (FAILURE);
	precise_usleep(philo, philo->table->time_to_sleep);
	return (SUCCESS);
}

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
	control_mutex(philo->second_fork, LOCK);
	if (write_status(philo, FORKING) == FAILURE)
	{
		control_mutex(philo->first_fork, UNLOCK);
		control_mutex(philo->second_fork, UNLOCK);
		return (FAILURE);
	}
	return (SUCCESS);
}

bool	write_status(t_philo *philo, char *msg)
{
	size_t	curr_time;

	curr_time = get_time() - philo->table->time_start;
	control_mutex(&philo->table->mtx_msg, LOCK);
	if (philo->table->finita_la_commedia == 1)
	{
		control_mutex(&philo->table->mtx_msg, UNLOCK);
		return (FAILURE);
	}
	printf("%zu %d %s\n", curr_time, philo->id, msg);
	control_mutex(&philo->table->mtx_msg, UNLOCK);
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

bool	sleeping(t_philo *philo)
{
	if (write_status(philo, SLEEPING) == FAILURE)
		return (FAILURE);
	precise_usleep(philo, philo->table->time_to_sleep);
}
