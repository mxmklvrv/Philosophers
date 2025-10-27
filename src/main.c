/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/27 13:32:28 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO:
int	main(int ac, char **av)
{
	t_trattoria	table;

	if (check_arg_count(ac) == FAILURE)
		return (FAILURE);
	if (check_input(av) == FAILURE)
		return (FAILURE);
	if (init_data(ac, av, &table) == FAILURE)
		return (FAILURE);
	if (start_simulation(&table) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

bool	start_simulation(t_trattoria *table)
{
	if (creat_threads(table) == FAILURE)
		return (wipe_off(table), FAILURE);
    join_threads(table, table->philo_nbr);
    wipe_off(table);
    return (SUCCESS);
}

bool	create_threads(t_trattoria *table)
{
	int	i;
    pthread_t waiter;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (control_threads(&table->philos[i].thread, &table->philos[i], dinner,
				CREATE) == FAILURE)
		{
			table->finita_la_commedia = 1;
			return (join_threads(table, i), FAILURE);
		}
	}
    if(control_threads(&waiter, table, serving_dinner, CREATE) == FAILURE)
        return (join_threads(table, table->philo_nbr), FAILURE);
	return (SUCCESS);
}


// join threads to wait others to finish simu
void	join_threads(t_trattoria *table, int qty)
{
	int	i;

	i = -1;
	while (++i < qty)
		control_threads(&table->philos[i].thread, NULL, NULL, JOIN);
}

// full quit
void	wipe_off(t_trattoria *table)
{
	if (!table)
		return ;
	destroy_forks(table, table->philo_nbr);
	control_mutex(&table->mtx_msg, DESTROY);
	control_mutex(&table->mtx_death, DESTROY);
	control_mutex(&table->mtx_portion, DESTROY);
	free_allocs(table);
}

void	destroy_forks(t_trattoria *table, int qty)
{
	int	i;

	i = -1;
	while (++i < qty)
		control_mutex(&table->forks[i], DESTROY);
}

// wrapper function to control threads (whta if join is failed)
bool	control_threads(pthread_t *th, void *data, void *(*function)(void *),
		t_oper oper)
{
	if (oper == CREATE)
	{
		if (pthread_create(th, NULL, function, data) != 0)
			return (error_message(ERROR_TH_CREATE), FAILURE);
	}
	else if (oper == JOIN)
		pthread_join(*th, NULL);
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

// free allocated memmory for *philos and *forks
void	free_allocs(t_trattoria *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

void	error_message(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return ;
}
