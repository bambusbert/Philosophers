/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:11:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/07 13:52:12 by slambert         ###   ########.fr       */
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

//TODO passt das, dass last_meal_time vor dem usleep
//auf 0 gesetzt wird?
void eat (t_single_philo *philo)
{
	print_status(philo->p_god, EATING, philo->id);
	philo->last_meal_time = return_time_in_ms();
	philo->times_eaten++;
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
	long long	time_since_last_meal;
	
	time_since_last_meal = return_time_in_ms() - philo->last_meal_time;
	if (time_since_last_meal > philo->time_to_die)
	{
		//philo starved
		set_end_simul(philo->p_god);
		print_status(philo->p_god, DEAD, philo->id);
		return 1;
	}
	if (philo->no_o_t_e_p_m_eat == philo->times_eaten)
	{
		//simulation ended without anyone dying
		set_end_simul(philo->p_god);
		return 1;
	}
	if (get_end_simul(philo->p_god) == 1)
		return 1;
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
			usleep(500);
		if (update_status(philo) == 1)
			break;
		take_left_fork(philo);
		if (update_status(philo) == 1)
			break;
		take_right_fork(philo);
		if (update_status(philo) == 1)
			break;
		eat(philo);
		if (update_status(philo) == 1)
			break;
		put_down_left_fork(philo);
		put_down_right_fork(philo);
		if (update_status(philo) == 1)
			break;
		sleeep(philo);
		think(philo);
		if (update_status(philo) == 1)
			break;
	}
	
	return ((void *)NULL);
}
