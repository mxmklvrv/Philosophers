/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:59:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/21 21:30:07 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//TODO:
// next is ti start digging in start of simulation
// thread creation and join
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
	else
		printf("ok\n"); // test output
}

bool start_simulation(t_trattoria *table)
{
    if(creat_threads(table) == FAILURE)
        return (wipe_off(table), FAILURE);
    
}

bool create_threads(t_trattoria *table)
{
    int i;
    
    i = -1;
    while (++i < table->philo_nbr)
    {
        if(control_threads(&table->philos[i].thread, &table->philos[i], dinner, CREATE) == FAILURE)
        {
            table->stop = 1;
            return (join_threads(table, i), FAILURE);
        }
    }
    return (SUCCESS);
}

void *dinner(void *arg)
{
    
}





// join threads to wait others to finish simu
void    join_threads(t_trattoria *table, int qty)
{
    int i;

    i = -1;
    while(++i < qty)
        control_threads(&table->philos[i].thread, NULL, NULL, JOIN);
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

// checks int for 0 and overflow 
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

// init all the data 
bool	init_data(int ac, char **av, t_trattoria *table)
{
	if (init_table(ac, av, table) == FAILURE)
		return (free_allocs(table), FAILURE);
	if (init_mutexes(table) == FAILURE)
		return (free_allocs(table), FAILURE);
	init_philos(table);
	return (SUCCESS);
}

// init table struct 
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
    table->stop = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (error_message(ERROR_MEM), FAILURE);
	table->forks = malloc(sizeof(t_pmtx) * table->philo_nbr);
	if (!table->forks)
		return (error_message(ERROR_MEM), FAILURE);
	return (SUCCESS);
}

// maybe mass mutex destroyer so i pass table and 3 more of mutexes 
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
	if(control_mutex(&table->mtx_msg, INIT) == FAILURE)
        return (destroy_forks(table, table->philo_nbr), FAILURE);
    if(control_mutex(&table->mtx_portion, INIT) == FAILURE)
    {
        control_mutex(&table->mtx_msg, DESTROY);
        return (destroy_forks(table, table->philo_nbr), FAILURE);
    }
    if(control_mutex(&table->mtx_stop, INIT) == FAILURE)
    {
        control_mutex(&table->mtx_msg, DESTROY);
        control_mutex(&table->mtx_portion, DESTROY);
        return (destroy_forks(table, table->philo_nbr), FAILURE);
    }
	return (SUCCESS);
}
// full quit
void    wipe_off(t_trattoria *table)
{
    if(!table)
        return;
    destroy_forks(table, table->philo_nbr);
    // probably need to add thread reemover or so
    control_mutex(&table->mtx_msg,DESTROY);
    control_mutex(&table->mtx_stop, DESTROY);
    control_mutex(&table->mtx_portion, DESTROY);
    free_allocs(table);
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
		assign_forks(table, philo, i);
		i++;
	}
}
void	assign_forks(t_trattoria *table, t_philo *philo, int i)
{
	if (philo->id % 2) // odd
	{
		philo->first_fork = &table->forks[(i + 1) % table->philo_nbr]; // rigth
		philo->second_fork = &table->forks[i];                         // left
	}
	else // even
	{
		philo->first_fork = &table->forks[i];                           // left
		philo->second_fork = &table->forks[(i + 1) % table->philo_nbr]; // right
	}
}

void	destroy_forks(t_trattoria *table, int qty)
{
	int i;

    i = -1;
    while(++i < qty)
        control_mutex(&table->forks[i], DESTROY);
}

// wrapper function to control threads (whta if join is failed)
bool    control_threads(pthread_t *th, void *data, void *(*function)(void *), t_oper oper)
{
    if(oper == CREATE)
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

// get_time in milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
// get int from the input 
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

void	error_message(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return ;
}
