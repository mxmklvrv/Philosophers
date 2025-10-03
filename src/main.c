/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/03 19:30:45 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_trattoria	table;

	if (check_arg_count(ac) == FAILURE)
		return (FAILURE);
	if (check_input(av) == FAILURE)
		return (FAILURE);
}

bool	check_arg_count(int ac)
{
	if (ac != 5 && ac != 6)
	{
		error_message(ERROR_AC ERROR_AC1 ERROR_AC2);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	error_message(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return ;
}

bool	check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j] && is_space(av[i][j]))
			j++;
		if (av[i][j] == '\0')
		{
			error_message(ERROR_EMPT);
			return (FAILURE);
		}
		while (av[i][j])
		{
			// we need only numbers
			// also detect for negative sign
		}
	}
}
