/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:40:21 by slambert          #+#    #+#             */
/*   Updated: 2026/05/25 11:43:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_until_ready(t_god_struct *p_god)
{
	while (get_simul_ready(p_god) == 0 && get_end_simul(p_god) == 0)
		usleep(500);
}

int	eat(t_single_philo *philo)
{
	if (update_status_one_philo(philo) == 1)
		return (1);
	set_t_last_meal(philo, return_time_in_ms());
	print_status(philo->p_god, EATING, philo->id);
	increment_times_eaten(philo);
	if (update_status_one_philo(philo) == 1)
		return (1);
	ft_usleep(philo->time_to_eat * 1000, philo);
	return (0);
}

int	sleeep(t_single_philo *philo)
{
	if (update_status_one_philo(philo) == 1)
		return (1);
	print_status(philo->p_god, SLEEPING, philo->id);
	ft_usleep(philo->time_to_sleep * 1000, philo);
	return (0);
}

int	think(t_single_philo *philo)
{
	long long	t_think;

	if (update_status_one_philo(philo) == 1)
		return (1);
	print_status(philo->p_god, THINKING, philo->id);
	if (philo->p_god->no_phil % 2 != 0)
	{
		t_think = philo->time_to_eat - philo->time_to_sleep;
		if (t_think < 0)
			t_think = 0;
		ft_usleep((t_think * 1000) + 1000, philo);
	}
	return (0);
}
