/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 17:50:56 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_left_fork(t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->fork_left);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
	return (0);
}

int	take_right_fork(t_single_philo *philo)
{
	if (update_status(philo) == 1)
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

// TODO passt das, dass time_last_meal vor dem usleep
// auf 0 gesetzt wird?
int	eat(t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return (1);
	print_status(philo->p_god, EATING, philo->id);
	// philo->time_last_meal = return_time_in_ms();
	set_t_last_meal(philo, return_time_in_ms());
	// philo->times_eaten++;
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
	// usleep (philo->time_to_ * 1000);
	return (0);
}

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
	// time_last_meal = return_time_in_ms() - philo->time_last_meal;
	time_last_meal = return_time_in_ms() - get_t_last_meal(philo);
	if (time_last_meal > philo->time_to_die)
	{
		// philo starved
		set_end_simul(philo->p_god);
		print_status(philo->p_god, DEAD, philo->id);
		return (1);
	}
	return (0);
}
void	philo_routine_loop (t_single_philo *philo)
{
	while (1)
	{
		if (philo->group == GROUP_ODD)
			usleep(700);
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

void single_philo_routine (t_single_philo *philo)
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
	t_single_philo *philo;
	
	philo = (t_single_philo *)arg;
	wait_until_ready(philo->p_god);
	if (philo->p_god->num_of_philosophers == 1)
		single_philo_routine(philo);
	else
		philo_routine_loop(philo);
	return ((void *)NULL);
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