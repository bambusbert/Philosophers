/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:48:13 by slambert          #+#    #+#             */
/*   Updated: 2026/05/16 18:38:13 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_global_mutexes(t_god_struct *p_god)
{
	long	i;

	if (pthread_mutex_init(&p_god->simul_ready_mutex, NULL) != 0)
		return (ERROR_HARD);
	if (pthread_mutex_init(&p_god->print_mutex, NULL) != 0)
		return (ERROR_HARD);
	i = -1;
	while (++i < p_god->no_phil)
	{
		if (pthread_mutex_init(&p_god->forks[i], NULL) != 0)
		{
			p_god->forks_initialized = i;
			return (ERROR_HARD);
		}
	}
	p_god->forks_initialized = p_god->no_phil;
	if (pthread_mutex_init(&p_god->simul_ended_mutex, NULL) != 0)
		return (ERROR_HARD);
	if (pthread_mutex_init(&p_god->philo_add_mutex, NULL) != 0)
		return (ERROR_HARD);
	return (RET_OK);
}

int	init_philo_mutexes(t_single_philo *philo)
{
	if (!philo)
		return (ERROR_HARD);
	if (pthread_mutex_init(&philo->time_last_meal_mutex, NULL) != 0)
		return (ERROR_HARD);
	if (pthread_mutex_init(&philo->times_eaten_mutex, NULL) != 0)
		return (ERROR_HARD);
	return (RET_OK);
}

int	initialize_everything(t_god_struct *p_god)
{
	if (zero_check(p_god) == ERROR_HARD)
	{
		printf("one or more values are zero\n");
		cleanup_everything(p_god);
		return (ERROR_HARD);
	}
	if (init_global_mutexes(p_god) == ERROR_HARD)
	{
		printf("critical error in init_global_mutexes\n");
		cleanup_everything(p_god);
		return (ERROR_HARD);
	}
	if (create_philo_threads(p_god) == ERROR_HARD)
	{
		printf("critical error in create_philo_threads\n");
		cleanup_everything(p_god);
		return (ERROR_HARD);
	}
	return (RET_OK);
}
