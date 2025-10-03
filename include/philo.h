/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:53:02 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/03 16:31:19 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <limits.h>  // INT_MAX
# include <pthread.h> // mutex
# include <stdio.h>   // printf
# include <stdlib.h>  // malloc free
# include <sys/time.h>
# include <unistd.h> // write usleep



typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				portion_count;
	int				last_portion;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_trattoria		*trattoria;
}					t_philo;

typedef struct s_trattoria
{
	int				philo_nbr;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_slep;
	size_t			time_start;
	int				portion_limit;
	t_fork			*forks;
	t_philo			*philos;
}					t_trattoria;

#endif