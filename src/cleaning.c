/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:13:21 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/31 12:45:32 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	join_threads(t_trattoria *table, int qty)
{
	int	i;

	i = -1;
	while (++i < qty)
	{
		if (control_threads(&table->philos[i].thread, NULL, NULL,
				JOIN) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

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
