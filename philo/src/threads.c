/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:12:55 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 18:13:22 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 *	1. initialize the philo struct
 *	2. start the philo thread with that struct as the argument
 */
static int	create_philo_thread(t_god_struct *p_god, int i)
{
	t_single_philo	*philo;

	philo = init_philo_struct(p_god, i);
	if (!philo)
		return (ERROR_HARD);
	if (pthread_create(&(p_god->threads[i]), NULL, philo_routine,
			(void *)philo) != 0)
		return (ERROR_HARD);
	return (RET_OK);
}

int	create_philo_threads(t_god_struct *p_god)
{
	int	i;

	i = -1;
	while (++i < p_god->num_of_philosophers)
	{
		if (create_philo_thread(p_god, i) == ERROR_HARD)
			return (ERROR_HARD);
	}
	return (RET_OK);
}

void	wait_for_philo_threads(t_god_struct *p_god)
{
	int	i;

	i = -1;
	while (++i < p_god->num_of_philosophers)
		pthread_join(p_god->threads[i], NULL);
}
