/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:41:33 by slambert          #+#    #+#             */
/*   Updated: 2026/05/24 13:21:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_left_fork(t_single_philo *philo)
{
	if (update_status_one_philo(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->fork_left);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
	return (0);
}

int	take_right_fork(t_single_philo *philo)
{
	if (update_status_one_philo(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->fork_right);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
	return (0);
}

void	put_down_left_fork(t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
}

void	put_down_right_fork(t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
}

void	put_down_both_forks(t_single_philo *philo)
{
	put_down_left_fork(philo);
	put_down_right_fork(philo);
}
