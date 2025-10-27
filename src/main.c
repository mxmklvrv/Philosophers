/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/27 15:15:11 by mklevero         ###   ########.fr       */
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

