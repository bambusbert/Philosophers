/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:52:50 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:53:31 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_simul_ready(t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ready_mutex);
	p_god->ready = 1;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
}

void	set_end_simul(t_god_struct *p_god)
{
	pthread_mutex_lock(&p_god->simul_ended_mutex);
	p_god->simul_ended = 1;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
}

void	set_t_last_meal(t_single_philo *philo, long long time)
{
	pthread_mutex_lock(&philo->time_last_meal_mutex);
	philo->time_last_meal = time;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
}

void	increment_times_eaten(t_single_philo *philo)
{
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
}
