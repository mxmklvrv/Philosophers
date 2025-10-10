/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:53:02 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/10 12:16:09 by mklevero         ###   ########.fr       */
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
typedef pthread_mutex_t		t_pmtx;

// error messages
# define ERROR_AC "Wrong number of arguments\nUsage: [number_of_philosophers] "
# define ERROR_AC1 "[time_to_die] [time_to_eat] [time_to_sleep] (optional "
# define ERROR_AC2 "[number_of_times_each_philosopher_must_eat])\n"
# define ERROR_EMPT "Error: Empty input\n"
# define ERROR_INPT "Error: Only digidts allowed\n"
# define ERROR_NGTV "Error: Negative numbers are not allowed\n"
# define ERROR_OVRF "Error: Overflow detected\n"
# define ERROR_ZERO "Error: Number cannot be 0\n"
# define ERROR_MEM "Error: memory allocation failed\n"

typedef enum e_oper
{
    DESTROY,
    INIT,
    LOCK,
    DETACH,
    UNLOCK,
    JOIN,
    CREATE,
} t_oper;


typedef struct s_philo
{
	int						id;
	int						portion_count;
	int						last_portion_time;
	pthread_t				thread;
	t_pmtx					*first_fork;
	t_pmtx					*second_fork;
	t_trattoria				*table;
}							t_philo;

typedef struct s_trattoria
{
	int						philo_nbr;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					time_start;
	int						portion_limit;
	t_pmtx					*forks;
	t_philo					*philos;
}							t_trattoria;

// main
int							main(int ac, char **av);

// validation
bool						check_arg_count(int ac);
bool						check_input(char **av);
bool						is_overflow_or_zero(const char *str);

// init_data
bool						init_data(int ac, char **av, t_trattoria *table);
bool	                    init_table(int ac, char **av, t_trattoria *table);
void                        init_philos(t_trattoria *table);
void                        assign_forks(t_trattoria *table, t_philo *philo, int i);
int							get_int(const char *str);
size_t						get_time(void);
// mutex 
bool   control_mutex(t_pmtx *mutex, t_oper oper);


// errors and free
void						error_message(const char *msg);
void	free_allocs(t_trattoria *table);

// utils
size_t						ft_strlen(const char *s);
bool						ft_isspace(char c);
bool						ft_isdigit(char c);

#endif