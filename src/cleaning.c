/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:13:21 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/27 15:18:08 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// destroy forks 
void	destroy_forks(t_trattoria *table, int qty)
{
	int	i;

	i = -1;
	while (++i < qty)
		control_mutex(&table->forks[i], DESTROY);
}

// join threads to wait others to finish dinner
void	join_threads(t_trattoria *table, int qty)
{
	int	i;

	i = -1;
	while (++i < qty)
		control_threads(&table->philos[i].thread, NULL, NULL, JOIN);
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
