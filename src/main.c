/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/09 18:22:29 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// remove below
// #include <limits.h>  // INT_MAX
// #include <pthread.h> // mutex
// #include <stdbool.h> // true/false
// #include <stdio.h>   // printf
// #include <stdlib.h>  // malloc free
// #include <sys/time.h>
// #include <unistd.h> // write usleep

// bool	ft_isdigit(char c);
// size_t	ft_strlen(const char *s);
// bool	ft_isspace(char c);
// bool	check_input(char **av);
// void	error_message(const char *msg);
// bool	check_arg_count(int ac);
// int		get_int(const char *str);
// bool	is_overflow_or_zero(const char *str);
// bool	init_data(int ac, char **av, t_trattoria *table);
// void	full_free(t_trattoria *table);

// solid input ./philo 4 800 200 200 [5]

// remove up

int	main(int ac, char **av)
{
	t_trattoria	table;

	if (check_arg_count(ac) == FAILURE)
		return (FAILURE);
	if (check_input(av) == FAILURE)
		return (FAILURE);
	if (init_data(ac, av, &table) == FAILURE)
		return (FAILURE);
	else
		printf("ok\n"); // test output
}

bool	init_data(int ac, char **av, t_trattoria *table)
{
	if (init_table(ac, av, table) == FAILURE)
        return (FAILURE);
    init_philos(table);
    
	return (SUCCESS);
}

void init_philos(t_trattoria *table)
{
    int i;
    t_philo *philo;
    
    i = 0;
    while(i < table->philo_nbr)
    {
       philo = table->philos + i;
       philo->id = i + 1;
       philo->portion_count = 0;
       philo->table = table;
       assign_forks(table, philo, i);
       i++;
    }
    
}

void    assign_forks(t_trattoria *table, t_philo *philo, int i)
{
    if(philo->id % 2) // odd
    {
        philo->first_fork = &table->forks[(i + 1) % table->philo_nbr]; // rigth
        philo->second_fork = &table->forks[i]; // left
    }
    else // even 
    {
        philo->first_fork = &table->forks[i]; // left
        philo->second_fork = &table->forks[(i + 1) % table->philo_nbr]; // right
    }
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
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
    if(!table->philos)
        return(error_message(ERROR_MEM), FAILURE);
	table->forks = malloc(sizeof(t_pmtx) * table->philo_nbr);
    if(!table->forks)
    {
        full_free(table);
        return(error_message(ERROR_MEM), FAILURE);
    }
    return (SUCCESS);
}


void	full_free(t_trattoria *table)
{
	free(table->philos);
	free(table->forks);
}

// get_time in milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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

// // remove from main below, for test usage
// bool	ft_isdigit(char c)
// {
// 	return (c >= '0' && c <= '9');
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
// bool	ft_isspace(char c)
// {
// 	return ((c >= 9 && c <= 13) || c == 32);
// }
// // remove from main up, for test usage