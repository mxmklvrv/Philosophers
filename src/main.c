/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/05 14:27:44 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// remove below
# include <limits.h>  // INT_MAX
# include <pthread.h> // mutex
# include <stdbool.h> // true/false
# include <stdio.h>   // printf
# include <stdlib.h>  // malloc free
# include <sys/time.h>
# include <unistd.h> // write usleep

bool	ft_isdigit(char c);
size_t	ft_strlen(const char *s);
bool	is_space(char c);
bool	check_input(char **av);
void	error_message(const char *msg);
bool	check_arg_count(int ac);
// remove up 

int	main(int ac, char **av)
{
	t_trattoria	table;

	if (check_arg_count(ac) == FAILURE)
		return (FAILURE);
	if (check_input(av) == FAILURE)
		return (FAILURE);
    else
        printf("ok\n");
    
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

// "      1123" ok
// "     -123" not ok
// "   +1234asdf" not ok
// "    sdf  " not ok

bool	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j] && is_space(av[i][j]))
			j++;
		if (av[i][j] == '\0')
            return (error_message(ERROR_EMPT), FAILURE);
        if (av[i][j] == '-')
            return (error_message(ERROR_NGTV), FAILURE);
		while (av[i][j] && ft_isdigit(av[i][j]))
			j++;
		if (av[i][j] != '\0')	
			return (error_message(ERROR_INPT), FAILURE);
        i++;
    }
    return (SUCCESS);
}

// remove from main below, for test usage
bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
// remove from main up, for test usage