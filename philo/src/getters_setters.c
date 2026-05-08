/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:49:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/08 14:50:31 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void set_simul_ready (t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ready_mutex);
	p_god->ready = 1;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
}

int get_simul_ready (t_god_struct *p_god)
{
	int ret;
	
	pthread_mutex_lock(&p_god->simul_ready_mutex);
	ret = p_god->ready;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
	return ret;
}

void	set_end_simul(t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ended_mutex);
	p_god->simul_ended = 1;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
}

int	get_end_simul(t_god_struct *p_god)
{
	int	ret;

	pthread_mutex_lock(&p_god->simul_ended_mutex);
	ret = p_god->simul_ended;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
	return (ret);
}
