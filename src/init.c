/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:45:43 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/30 20:20:11 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_data(int ac, char **av, t_trattoria *table)
{
	if (init_table(ac, av, table) == FAILURE)
		return (free_allocs(table), FAILURE);
	if (init_mutexes(table) == FAILURE)
		return (free_allocs(table), FAILURE);
	init_philos(table);
	return (SUCCESS);
}

bool	init_table(int ac, char **av, t_trattoria *table)
{
	table->philo_nbr = get_int(av[1]);
	table->time_to_die = get_int(av[2]);
	table->time_to_eat = get_int(av[3]);
	table->time_to_sleep = get_int(av[4]);
	if (ac == 6)
		table->portion_limit = get_int(av[5]);
	else
		table->portion_limit = -1;
	table->time_start = get_time();
	table->finita_la_commedia = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (error_message(ERROR_MEM), FAILURE);
	table->forks = malloc(sizeof(t_pmtx) * table->philo_nbr);
	if (!table->forks)
		return (error_message(ERROR_MEM), FAILURE);
	return (SUCCESS);
}

bool	init_mutexes(t_trattoria *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (control_mutex(&table->forks[i], INIT) == FAILURE)
			return (destroy_forks(table, i), FAILURE);
		i++;
	}
	if (control_mutex(&table->mtx_msg, INIT) == FAILURE)
		return (destroy_forks(table, table->philo_nbr), FAILURE);
	if (control_mutex(&table->mtx_portion, INIT) == FAILURE)
	{
		control_mutex(&table->mtx_msg, DESTROY);
		return (destroy_forks(table, table->philo_nbr), FAILURE);
	}
	if (control_mutex(&table->mtx_death, INIT) == FAILURE)
	{
		control_mutex(&table->mtx_msg, DESTROY);
		control_mutex(&table->mtx_portion, DESTROY);
		return (destroy_forks(table, table->philo_nbr), FAILURE);
	}
	return (SUCCESS);
}

void	init_philos(t_trattoria *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->portion_count = 0;
		philo->table = table;
		philo->last_portion_time = table->time_start;
		assign_forks(table, philo, i);
		i++;
	}
}

// odd right left, even left right
void	assign_forks(t_trattoria *table, t_philo *philo, int i)
{
	if (philo->id % 2)
	{
		philo->first_fork = &table->forks[(i + 1) % table->philo_nbr];
		philo->second_fork = &table->forks[i];
	}
	else
	{
		philo->first_fork = &table->forks[i];
		philo->second_fork = &table->forks[(i + 1) % table->philo_nbr];
	}
}
