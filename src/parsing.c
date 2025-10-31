/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:49:32 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/31 12:46:34 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_arg_count(int ac)
{
	if (ac != 5 && ac != 6)
	{
		error_message(ERROR_AC ERROR_AC1 ERROR_AC2);
		return (FAILURE);
	}
	return (SUCCESS);
}

bool	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j] && ft_isspace(av[i][j]))
			j++;
		if (av[i][j] == '\0')
			return (error_message(ERROR_EMPT), FAILURE);
		if (av[i][j] == '-')
			return (error_message(ERROR_NGTV), FAILURE);
		while (av[i][j] && ft_isdigit(av[i][j]))
			j++;
		if (av[i][j] != '\0')
			return (error_message(ERROR_INPT), FAILURE);
		if (is_overflow_or_zero(av[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

bool	is_overflow_or_zero(const char *str)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (error_message(ERROR_OVRF), FAILURE);
		i++;
	}
	if (res == 0)
		return (error_message(ERROR_ZERO), FAILURE);
	return (SUCCESS);
}

int	get_int(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}
