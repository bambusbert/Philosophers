/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:13:52 by slambert          #+#    #+#             */
/*   Updated: 2026/05/07 12:09:22 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long return_time_in_ms()
{
	struct timeval tv;
	long long time_sec;
	long long time_usec;
	long long time_msec;
	
	gettimeofday(&tv, NULL);
	time_sec = (long long) tv.tv_sec;
	time_usec = (long long) tv.tv_usec;
	time_msec = time_sec * 1000 + time_usec / 1000;
	return time_msec;
}

long long return_delta_time(t_god_struct *p_god)
{
	return return_time_in_ms() - p_god->start_time;
}

// long long return_time_since_last_meal(t_single_philo *philo)
// {
// 	long long t_s_l_m;

	
// }