/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:07:58 by slambert          #+#    #+#             */
/*   Updated: 2026/05/22 12:55:07 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status_error(t_god_struct *p_god, char *msg)
{
	pthread_mutex_lock(&p_god->print_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(&p_god->print_mutex);
}

void	print_status(t_god_struct *p_god, int event, int id)
{
	if (event == DEAD)
		print_status_died(p_god, id);
	if (get_end_simul(p_god) == 1)
	{
		return ;
	}
	if (event == FORK_TAKEN)
		print_status_fork(p_god, id);
	else if (event == EATING)
		print_status_eating(p_god, id);
	else if (event == SLEEPING)
		print_status_sleeping(p_god, id);
	else if (event == THINKING)
		print_status_thinking(p_god, id);
	else
		print_status_error(p_god, "something drastically went wrong");
}
