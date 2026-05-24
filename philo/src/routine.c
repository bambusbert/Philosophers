/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/24 14:37:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	even_strat(t_single_philo *philo)
{
	if (take_left_fork(philo) == 1)
		return (1);
	if (take_right_fork(philo) == 1)
	{
		put_down_left_fork(philo);
		return (1);
	}
	return (0);
}

static int	odd_strat(t_single_philo *philo)
{
	if (take_right_fork(philo) == 1)
		return (1);
	if (take_left_fork(philo) == 1)
	{
		put_down_right_fork(philo);
		return (1);
	}
	return (0);
}

static void	philo_routine_loop(t_single_philo *philo)
{
	initial_delay(philo);
	while (1)
	{
		if (philo->group == GROUP_EVEN)
		{
			if (even_strat(philo) == 1)
				break ;
		}
		else if (odd_strat(philo) == 1)
			break ;
		if (eat(philo) == 1)
		{
			put_down_both_forks(philo);
			break ;
		}
		put_down_both_forks(philo);
		if (sleeep(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
}

static void	single_philo_routine(t_single_philo *philo)
{
	print_status_fork(philo->p_god, philo->id);
	ft_usleep(philo->time_to_die * 1000, philo);
	print_status_died(philo->p_god, philo->id);
	set_end_simul(philo->p_god);
}

void	*philo_routine(void *arg)
{
	t_single_philo	*philo;

	philo = (t_single_philo *)arg;
	wait_until_ready(philo->p_god);
	if (philo->p_god->no_phil == 1)
		single_philo_routine(philo);
	else
		philo_routine_loop(philo);
	return (NULL);
}
