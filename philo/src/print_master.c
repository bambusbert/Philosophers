/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:07:58 by slambert          #+#    #+#             */
/*   Updated: 2026/05/08 14:22:07 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 *	TODO think about if i need a separate logic for death msgs
 */
void	print_status(t_god_struct *p_god, int event, int id)
{
	long long	timestamp;

	timestamp = return_delta_time(p_god);
	if (event == DEAD)
		print_status_died(p_god, timestamp, id);
	//pthread_mutex_lock(&p_god->simul_ended_mutex);
	if (get_end_simul(p_god) == 1)
	{
		//pthread_mutex_unlock(&p_god->simul_ended_mutex);
		return ;
	}
	//pthread_mutex_unlock(&p_god->simul_ended_mutex);
	if (event == FORK_TAKEN)
		print_status_fork(p_god, timestamp, id);
	else if (event == EATING)
		print_status_eating(p_god, timestamp, id);
	else if (event == SLEEPING)
		print_status_sleeping(p_god, timestamp, id);
	else if (event == THINKING)
		print_status_thinking(p_god, timestamp, id);
	else
	{
		pthread_mutex_lock(&p_god->print_mutex);
		printf("if you see that something drastically went wrong\n");
		pthread_mutex_unlock(&p_god->print_mutex);
	}
}
