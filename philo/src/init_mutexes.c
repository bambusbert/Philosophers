/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:48:13 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:51:00 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// TODO protect against failure
void	init_global_mutexes(t_god_struct *p_god)
{
	long	i;

	pthread_mutex_init(&p_god->simul_ready_mutex, NULL);
	pthread_mutex_init(&p_god->print_mutex, NULL);
	i = -1;
	while (++i < p_god->no_phil)
		pthread_mutex_init(&p_god->forks[i], NULL);
	pthread_mutex_init(&p_god->simul_ended_mutex, NULL);
	pthread_mutex_init(&p_god->philo_add_mutex, NULL);
}

void	init_philo_mutexes(t_single_philo *philo)
{
	if (!philo)
		return ;
	pthread_mutex_init(&philo->time_last_meal_mutex, NULL);
	pthread_mutex_init(&philo->times_eaten_mutex, NULL);
}
