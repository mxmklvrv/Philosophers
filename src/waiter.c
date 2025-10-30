/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:03:51 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/30 14:14:58 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			break ;
		usleep(500);
	}
	return (NULL);
}
// checks if all ate
bool	bill_needed(t_trattoria *table)
{
	int	i;
	int	full;

	i = -1;
	full = 0;
	if (table->portion_limit == -1)
		return (FAILURE);
	while (++i < table->philo_nbr)
	{
		control_mutex(&table->mtx_portion, LOCK);
		if (table->philos[i].portion_count >= table->portion_limit)
			full++;
		control_mutex(&table->mtx_portion, UNLOCK);
	}
	if (full == table->philo_nbr)
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

// new still alive function which declears death as well. 
bool	still_alive(t_trattoria *table, int i)
{
	size_t	curr_time;

	curr_time = get_time();
	if (curr_time - table->philos[i].last_portion_time >= table->time_to_die)
	{
		control_mutex(&table->mtx_death, LOCK);
		if(table->finita_la_commedia == 0)
        {
            table->finita_la_commedia = 1;
            control_mutex(&table->mtx_death, UNLOCK);
            control_mutex(&table->mtx_msg, LOCK);
            printf("%zu %d %s\n", curr_time - table->time_start, table->philos[i].id, DIED);
		    control_mutex(&table->mtx_msg, UNLOCK);
        }
        else
            control_mutex(&table->mtx_death, UNLOCK);
		return (FAILURE);
	}
	return (SUCCESS);
}
