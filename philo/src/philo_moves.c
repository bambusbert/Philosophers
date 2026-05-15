/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:40:21 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:43:22 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	eat(t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return (1);
	print_status(philo->p_god, EATING, philo->id);
	set_t_last_meal(philo, return_time_in_ms());
	increment_times_eaten(philo);
	if (update_status(philo) == 1)
		return (1);
	usleep(philo->time_to_eat * 1000);
	return (0);
}

int	sleeep(t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return (1);
	print_status(philo->p_god, SLEEPING, philo->id);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

int	think(t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return (1);
	print_status(philo->p_god, THINKING, philo->id);
	return (0);
}
