/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:53:02 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/27 17:10:54 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <limits.h>    // INT_MAX
# include <pthread.h>   // mutex
# include <stdatomic.h> // atomic ints
# include <stdbool.h>   // true/false
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc free
# include <sys/time.h>
# include <unistd.h> // write usleep

# define SUCCESS 0
# define FAILURE 1

typedef struct s_trattoria	t_trattoria;
typedef pthread_mutex_t		t_pmtx;

// error messages
# define ERROR_AC "Invalid Wrong number of arguments\nUsage: [number_of_philosophers] "
# define ERROR_AC1 "[time_to_die] [time_to_eat] [time_to_sleep] (optional "
# define ERROR_AC2 "[number_of_times_each_philosopher_must_eat])\n"
# define ERROR_EMPT "Invalid: Empty input\n"
# define ERROR_INPT "Invalid: Only digidts allowed\n"
# define ERROR_NGTV "Invalid: Negative numbers are not allowed\n"
# define ERROR_OVRF "Invalid: Overflow detected\n"
# define ERROR_ZERO "Invalid: Number cannot be 0\n"
# define ERROR_MEM "Invalid: memory allocation failed\n"
# define ERROR_MTX_INIT "Invalid: mutex init failed\n"
# define ERROR_TH_CREATE "Invalid: pthread creation failed\n"

// action message
# define FORKING "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef enum e_oper
{
	DESTROY,
	INIT,
	LOCK,
	DETACH,
	UNLOCK,
	JOIN,
	CREATE,
}							t_oper;

typedef struct s_philo
{
	int						id;
	int						portion_count;
	size_t					last_portion_time;
	pthread_t				thread;
	t_pmtx					*first_fork;
	t_pmtx					*second_fork;
	t_trattoria				*table;
}							t_philo;

typedef struct s_trattoria
{
	int				finita_la_commedia;
	int						philo_nbr;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					time_start;
	int						portion_limit;
	t_philo					*philos;
	t_pmtx					*forks;
	t_pmtx					mtx_msg;
	t_pmtx					mtx_portion;
	t_pmtx					mtx_death;
}							t_trattoria;

// main
int							main(int ac, char **av);

// parsing
bool						check_arg_count(int ac);
bool						check_input(char **av);
bool						is_overflow_or_zero(const char *str);
int							get_int(const char *str);

// init
bool						init_data(int ac, char **av, t_trattoria *table);
bool						init_table(int ac, char **av, t_trattoria *table);
bool						init_mutexes(t_trattoria *table);
void						init_philos(t_trattoria *table);
void						assign_forks(t_trattoria *table, t_philo *philo,
								int i);

// controls
bool						start_simulation(t_trattoria *table);
bool						create_threads(t_trattoria *table);
bool						control_threads(pthread_t *th, void *data,
								void *(*function)(void *), t_oper oper);
bool						control_mutex(t_pmtx *mutex, t_oper oper);

// dinner
void						*dinner(void *arg);
bool						think(t_philo *philo);
bool						sleeping(t_philo *philo);
bool						eat(t_philo *philo);
bool						take_fork(t_philo *philo);
bool						write_status(t_philo *philo, char *msg);
bool						dead_man_found(t_philo *philo);
bool						sleeping(t_philo *philo);

// waiter
void						*serving_dinner(void *arg);
bool						bill_needed(t_trattoria *table);
bool						tomb_needed(t_trattoria *table);
bool						still_alive(t_trattoria *table, int i);

// utils
bool						ft_isdigit(char c);
size_t						ft_strlen(const char *s);
bool						ft_isspace(char c);
size_t						get_time(void);
void						precise_usleep(t_philo *philo, size_t ms);

// cleaning
void						wipe_off(t_trattoria *table);
void						destroy_forks(t_trattoria *table, int qty);
void						join_threads(t_trattoria *table, int qty);
void						free_allocs(t_trattoria *table);
void						error_message(const char *msg);

#endif