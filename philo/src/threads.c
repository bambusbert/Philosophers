/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:12:55 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 17:06:03 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//TODO do i need mutex here?
//i think no because it is before i call it before pthread_create
void add_philo_to_god_struct (t_single_philo *philo, t_god_struct *p_god)
{
	t_single_philo *current_philo;
	
	if (p_god->philos == NULL)
	{
		p_god->philos = philo;
		return ;
	}
	current_philo = p_god->philos;
	while (current_philo->next != NULL)
	{
		current_philo = current_philo->next;
	}
	current_philo->next = philo;
}

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
	add_philo_to_god_struct(philo, p_god);
	if (pthread_create(&(p_god->threads[i]), NULL, philo_routine,
			(void *)philo) != 0)
			{
				printf("errrrr\n");
				//pthread_join(philo->p_god->threads[i], NULL);
				return (ERROR_HARD);
			}
		
	
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
