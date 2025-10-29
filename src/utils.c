/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:18:26 by mklevero          #+#    #+#             */
/*   Updated: 2025/10/29 18:56:15 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

// get_time in milliseconds (current time)
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// for now void
void	precise_usleep(t_philo *philo, size_t ms)
{
	size_t start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (dead_man_found(philo) == SUCCESS)
			return ;
		usleep(500);
	}
}