/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 22:22:15 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_left_fork (t_single_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
}

void	take_right_fork (t_single_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
}

void	put_down_left_fork (t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
}

void	put_down_right_fork (t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
}

void eat (t_single_philo *philo)
{
	print_status(philo->p_god, EATING, philo->id);
	usleep (philo->time_to_eat * 1000);
}

void sleeep (t_single_philo *philo)
{
	print_status(philo->p_god, SLEEPING, philo->id);
	usleep (philo->time_to_sleep * 1000);
}

//gibt keine time_to_think, wie lösen? es wird nur gethinkt wenn es nicht anders geht
void think (t_single_philo *philo)
{
	print_status(philo->p_god, THINKING, philo->id);
	//usleep (philo->time_to_ * 1000);
}

// TODO:	create 2 different routines. A is applied to odd philosophers and 2 to even.
//			if there is an odd number of philosophers there has to be one that changes
//			groups after each cycle
void	*philo_routine(void *arg)
{
	t_single_philo	*philo;

	philo = (t_single_philo *)arg;
    say_hello(philo);
	
	// while (1)
	// {
	// 	take_left_fork(philo);
	// 	take_right_fork(philo);
	// 	eat(philo);
	// 	put_down_left_fork(philo);
	// 	put_down_right_fork(philo);
	// 	sleeep(philo);
	// 	think(philo);
	// }
	
	return ((void *)NULL);
}
