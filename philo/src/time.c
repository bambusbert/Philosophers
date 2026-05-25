/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:13:52 by slambert          #+#    #+#             */
/*   Updated: 2026/05/25 11:42:20 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	return_time_in_ms(void)
{
	struct timeval	tv;
	long long		time_sec;
	long long		time_usec;
	long long		time_msec;

	gettimeofday(&tv, NULL);
	time_sec = (long long)tv.tv_sec;
	time_usec = (long long)tv.tv_usec;
	time_msec = time_sec * 1000 + time_usec / 1000;
	return (time_msec);
}

long long	return_delta_time(t_god_struct *p_god)
{
	return (return_time_in_ms() - p_god->start_time);
}

void	ft_usleep(long usec, t_single_philo *philo)
{
	long long	start;
	long long	end;
	long long	current;

	start = return_time_in_ms();
	end = start + (usec / 1000);
	current = start;
	while (current < end)
	{
		if (get_end_simul(philo->p_god) == 1)
			break ;
		usleep(500);
		current = return_time_in_ms();
	}
}
