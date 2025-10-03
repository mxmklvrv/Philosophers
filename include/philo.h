/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:53:02 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/03 19:24:21 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <limits.h>  // INT_MAX
# include <pthread.h> // mutex
# include <stdbool.h> // true/false
# include <stdio.h>   // printf
# include <stdlib.h>  // malloc free
# include <sys/time.h>
# include <unistd.h> // write usleep

# define SUCCESS 0
# define FAILURE 1

typedef struct s_trattoria	t_trattoria;

// error messages
# define ERROR_AC "Wrong number of arguments\nUsage: [number_of_philosophers]"
# define ERROR_AC1 "[time_to_die] [time_to_eat] [time_to_sleep] (optional "
# define ERROR_AC2 "[number_of_times_each_philosopher_must_eat])\n"
# define ERROR_EMPT "Error: Empty input"


typedef struct s_fork
{
	pthread_mutex_t			fork;
	int						fork_id;
}							t_fork;

typedef struct s_philo
{
	int						id;
	int						portion_count;
	int						last_portion;
	t_fork					*left_fork;
	t_fork					*right_fork;
	pthread_t				thread;
	t_trattoria				*trattoria;
}							t_philo;

struct						s_trattoria
{
	int						philo_nbr;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_slep;
	size_t					time_start;
	int						portion_limit;
	t_fork					*forks;
	t_philo					*philos;
};

// main
int							main(int ac, char **av);

// validation
bool						check_arg_count(int ac);

// errors
void						error_message(const char *msg);
// utils
size_t						ft_strlen(const char *s);
bool						is_space(char c);

#endif