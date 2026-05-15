/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_slave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:07:58 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 17:43:05 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status_fork(t_god_struct *p_god, long long timestamp, int id)
{
	pthread_mutex_lock(&p_god->print_mutex);
	if (!get_end_simul(p_god))
		printf("%lld %d has taken a fork\n", timestamp, id + 1);
	pthread_mutex_unlock(&p_god->print_mutex);
}

void	print_status_eating(t_god_struct *p_god, long long timestamp, int id)
{
	pthread_mutex_lock(&p_god->print_mutex);
	if (!get_end_simul(p_god))
		printf("%lld %d is eating\n", timestamp, id + 1);
	pthread_mutex_unlock(&p_god->print_mutex);
}

void	print_status_sleeping(t_god_struct *p_god, long long timestamp, int id)
{
	pthread_mutex_lock(&p_god->print_mutex);
	if (!get_end_simul(p_god))
		printf("%lld %d is sleeping\n", timestamp, id + 1);
	pthread_mutex_unlock(&p_god->print_mutex);
}

void	print_status_thinking(t_god_struct *p_god, long long timestamp, int id)
{
	pthread_mutex_lock(&p_god->print_mutex);
	if (!get_end_simul(p_god))
		printf("%lld %d is thinking\n", timestamp, id + 1);
	pthread_mutex_unlock(&p_god->print_mutex);
}

void	print_status_died(t_god_struct *p_god, long long timestamp, int id)
{
	pthread_mutex_lock(&p_god->print_mutex);
	printf("%lld %d died\n", timestamp, id + 1);
	pthread_mutex_unlock(&p_god->print_mutex);
}

