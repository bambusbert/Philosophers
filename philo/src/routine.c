/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:51:00 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_until_ready(t_god_struct *p_god)
{
	while (get_simul_ready(p_god) == 0)
		usleep(500);
}

int	update_status(t_single_philo *philo)
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

void	philo_routine_loop(t_single_philo *philo)
{
	while (1)
	{
		if (philo->group == GROUP_ODD)
			usleep(1000);
		if (take_right_fork(philo) == 1)
			break ;
		if (take_left_fork(philo) == 1)
		{
			put_down_right_fork(philo);
			break ;
		}
		if (eat(philo) == 1)
		{
			put_down_left_fork(philo);
			put_down_right_fork(philo);
			break ;
		}
		put_down_left_fork(philo);
		put_down_right_fork(philo);
		if (sleeep(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
}

void	single_philo_routine(t_single_philo *philo)
{
	long long	timestamp;

	timestamp = return_delta_time(philo->p_god);
	print_status_fork(philo->p_god, timestamp, philo->id);
	usleep(philo->time_to_die * 1000);
	timestamp = return_delta_time(philo->p_god);
	print_status_died(philo->p_god, timestamp, philo->id);
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
	return ((void *) NULL);
}

/* void	*philo_routine(void *arg)
{
	t_single_philo *philo;

	philo = (t_single_philo *)arg;
	// say_hello(philo);
	wait_until_ready(philo->p_god);
	while (1)
	{
		if (philo->group == GROUP_ODD)
		{
			if (take_left_fork(philo) == 1)
				break ;
			if (take_right_fork(philo) == 1)
			{
				put_down_left_fork(philo);
				break ;
			}
		}
		else
		{
			if (take_right_fork(philo) == 1)
				break ;
			if (take_left_fork(philo) == 1)
			{
				put_down_right_fork(philo);
				break ;
			}
		}
		if (eat(philo) == 1)
		{
			put_down_left_fork(philo);
			put_down_right_fork(philo);
			break ;
		}
		put_down_left_fork(philo);
		put_down_right_fork(philo);
		if (sleeep(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
	return ((void *)NULL);
} */