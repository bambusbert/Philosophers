/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:13:52 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 19:14:15 by slambert         ###   ########.fr       */
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
