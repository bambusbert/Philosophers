/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:49:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 12:19:05 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void set_simul_ready (t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ready_mutex);
	p_god->ready = 1;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
}

int get_simul_ready (t_god_struct *p_god)
{
	int ret;
	
	pthread_mutex_lock(&p_god->simul_ready_mutex);
	ret = p_god->ready;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
	return ret;
}

void	set_end_simul(t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ended_mutex);
	p_god->simul_ended = 1;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
}

int	get_end_simul(t_god_struct *p_god)
{
	int	ret;

	pthread_mutex_lock(&p_god->simul_ended_mutex);
	ret = p_god->simul_ended;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
	return (ret);
}

//TODO brauch ich das?
/* void update_t_last_meal(t_single_philo *philo)
{
	pthread_mutex_lock(&philo->time_last_meal_mutex);
	philo->time_last_meal = return_time_in_ms() - philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
} */

void set_t_last_meal(t_single_philo *philo, long long time)
{
	pthread_mutex_lock(&philo->time_last_meal_mutex);
	philo->time_last_meal = time;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
}

long long get_t_last_meal(t_single_philo *philo)
{
	long long ret;
	
	pthread_mutex_lock(&philo->time_last_meal_mutex);
	ret = philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
	return ret;
}

void increment_times_eaten(t_single_philo *philo)
{
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
}

int get_times_eaten (t_single_philo *philo)
{
	int ret;
	
	pthread_mutex_lock(&philo->times_eaten_mutex);
	ret = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	return ret;
}
