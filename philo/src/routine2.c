/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:35:31 by slambert          #+#    #+#             */
/*   Updated: 2026/05/24 14:35:57 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	update_status_all(t_god_struct *p_god)
{
	t_single_philo	*philo;

	philo = p_god->philos;
	while (philo)
	{
		if (update_status_one_philo(philo) == 1)
			return (philo->id);
		philo = philo->next;
	}
	return (-1);
}

int	update_status_one_philo(t_single_philo *philo)
{
	long long	time_last_meal;

	if (get_end_simul(philo->p_god) == 1)
		return (1);
	time_last_meal = return_time_in_ms() - get_t_last_meal(philo);
	if (time_last_meal > philo->time_to_die)
	{
		set_end_simul(philo->p_god);
		print_status(philo->p_god, DEAD, philo->id);
		return (1);
	}
	return (0);
}

void	initial_delay(t_single_philo *philo)
{
	if (philo->group == GROUP_ODD && philo->status == INIT)
	{
		philo->status = HUNGRY;
		ft_usleep(2500, philo);
	}
}
