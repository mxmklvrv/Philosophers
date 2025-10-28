/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:08:42 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/28 14:19:02 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start simulation
bool	start_simulation(t_trattoria *table)
{
	if (create_threads(table) == FAILURE)
		return (wipe_off(table), FAILURE);
	if (join_threads(table, table->philo_nbr) == FAILURE)
		return (wipe_off(table), FAILURE);
	wipe_off(table);
	return (SUCCESS);
}

// philo and waiter threads creation
// not sure about waiter join
bool	create_threads(t_trattoria *table)
{
	int			i;
	pthread_t	waiter;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (control_threads(&table->philos[i].thread, &table->philos[i], dinner,
				CREATE) == FAILURE)
		{
			control_mutex(&table->mtx_death, LOCK);
			table->finita_la_commedia = 1;
			control_mutex(&table->mtx_death, UNLOCK);
			if (join_threads(table, i) == FAILURE)
				return (FAILURE);
			return (FAILURE);
		}
	}
	if (control_threads(&waiter, table, serving_dinner, CREATE) == FAILURE)
	{
		if (join_threads(table, table->philo_nbr) == FAILURE)
			return (FAILURE);
	}
	if (control_threads(&waiter, NULL, NULL, JOIN) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

// wrapper function to control threads
bool	control_threads(pthread_t *th, void *data, void *(*function)(void *),
		t_oper oper)
{
	if (oper == CREATE)
	{
		if (pthread_create(th, NULL, function, data) != 0)
			return (error_message(ERROR_TH_CREATE), FAILURE);
	}
	else if (oper == JOIN)
	{
		if (pthread_join(*th, NULL) != 0)
			return (error_message(ERROR_TH_JOIN), FAILURE);
	}
	return (SUCCESS);
}

// wrapper function to control mutexes
bool	control_mutex(t_pmtx *mutex, t_oper oper)
{
	if (oper == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (error_message(ERROR_MTX_INIT), FAILURE);
	}
	else if (oper == LOCK)
		pthread_mutex_lock(mutex);
	else if (oper == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (oper == DESTROY)
		pthread_mutex_destroy(mutex);
	return (SUCCESS);
}
