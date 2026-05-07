/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/07 16:54:16 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_left_fork (t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return 1;
	pthread_mutex_lock(philo->fork_left);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
	return 0;
}

int	take_right_fork (t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return 1;
	pthread_mutex_lock(philo->fork_right);
	print_status(philo->p_god, FORK_TAKEN, philo->id);
	return 0;
}

void	put_down_left_fork (t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
}

void	put_down_right_fork (t_single_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
}

//TODO passt das, dass time_last_meal vor dem usleep
//auf 0 gesetzt wird?
int eat (t_single_philo *philo)
{	
	if (update_status(philo) == 1)
		return 1;
	print_status(philo->p_god, EATING, philo->id);
	philo->time_last_meal = return_time_in_ms();
	philo->times_eaten++;
	if (update_status(philo) == 1)
		return 1;
	usleep (philo->time_to_eat * 1000);
	return 0;
}

int sleeep (t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return 1;
	print_status(philo->p_god, SLEEPING, philo->id);
	usleep (philo->time_to_sleep * 1000);
	return 0;
}

//gibt keine time_to_think, wie lösen? es wird nur gethinkt wenn es nicht anders geht
int think (t_single_philo *philo)
{
	if (update_status(philo) == 1)
		return 1;
	print_status(philo->p_god, THINKING, philo->id);
	//usleep (philo->time_to_ * 1000);
	return 0;
}

void wait_until_ready (t_god_struct *p_god)
{
	while (p_god->ready == 0)
	{
		
	}
}

void set_end_simul(t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ended_mutex);
	p_god->simul_ended = 1;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
}

int get_end_simul(t_god_struct *p_god)
{
	int ret;
	
	pthread_mutex_lock(&p_god->simul_ended_mutex);
	ret = p_god->simul_ended;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
	return ret;
}

int update_status (t_single_philo *philo)
{
	long long	time_last_meal;
	
	if (get_end_simul(philo->p_god) == 1)
		return 1;
	time_last_meal = return_time_in_ms() - philo->time_last_meal;
	if (time_last_meal > philo->time_to_die)
	{
		//philo starved
		set_end_simul(philo->p_god);
		print_status(philo->p_god, DEAD, philo->id);
		return 1;
	}
	//TODO this is wrong, actually ALL philosophers have to 
	// if (philo->no_o_t_e_p_m_eat == philo->times_eaten)
	// {
	// 	//simulation ended without anyone dying
	// 	set_end_simul(philo->p_god);
	// 	return 1;
	// }
	return 0;
}

/* int check_if_philo_dead(t_single_philo *philo)
{
	if (ret)
} */

// TODO:	create 2 different routines. A is applied to odd philosophers and 2 to even.
//			if there is an odd number of philosophers there has to be one that changes
//			groups after each cycle
void	*philo_routine(void *arg)
{
	t_single_philo	*philo;

	philo = (t_single_philo *)arg;
    //say_hello(philo);
	wait_until_ready(philo->p_god);
	while (1)
	{
		if (philo->group == GROUP_ODD)
			usleep(2000);
		if (take_left_fork(philo) == 1)
			break;
		if (take_right_fork(philo) == 1)
			break;
		// if (update_status(philo) == 1)
		// 	break;
		if (eat(philo) == 1)
			break;
		put_down_left_fork(philo);
		put_down_right_fork(philo);
		if (sleeep(philo) == 1)
			break;
		if (think(philo) == 1)
			break;
	}
	
	return ((void *)NULL);
}
