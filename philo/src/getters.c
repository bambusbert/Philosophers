/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:49:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:53:32 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_simul_ready(t_god_struct *p_god)
{
	int	ret;

	pthread_mutex_lock(&p_god->simul_ready_mutex);
	ret = p_god->ready;
	pthread_mutex_unlock(&p_god->simul_ready_mutex);
	return (ret);
}

int	get_end_simul(t_god_struct *p_god)
{
	int	ret;

	pthread_mutex_lock(&p_god->simul_ended_mutex);
	ret = p_god->simul_ended;
	pthread_mutex_unlock(&p_god->simul_ended_mutex);
	return (ret);
}

long long	get_t_last_meal(t_single_philo *philo)
{
	long long	ret;

	pthread_mutex_lock(&philo->time_last_meal_mutex);
	ret = philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
	return (ret);
}

int	get_times_eaten(t_single_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->times_eaten_mutex);
	ret = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	return (ret);
}
