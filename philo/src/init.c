/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:34:39 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 15:37:01 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void assign_forks(t_god_struct *p_god, t_single_philo *philo)
{
	if (philo->id == 0)
	{
		philo->fork_left = &p_god->forks[0];
		philo->fork_right = &p_god->forks[p_god->num_of_philosophers - 1];
		return;
	}
	philo->fork_left = &p_god->forks[philo->id];
	philo->fork_right = &p_god->forks[philo->id - 1];
}

t_god_struct	*create_god_struct(char **argv)
{
	t_god_struct	*p_god;

	p_god = ft_calloc(1, sizeof(t_god_struct));
	if (!p_god)
		return (NULL);
	p_god->num_of_philosophers = ft_atoi(argv[1]);
	p_god->time_to_die = ft_atoi(argv[2]);
	p_god->time_to_eat = ft_atoi(argv[3]);
	p_god->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p_god->no_o_t_e_p_m_eat = ft_atoi(argv[5]);
	else
		p_god->no_o_t_e_p_m_eat = -1;
	p_god->shit_list = NULL;
	p_god->threads = ft_calloc(p_god->num_of_philosophers, sizeof(pthread_t));
	if (!p_god->threads)
		return (free(p_god), NULL);
	if (add_to_shit_list(p_god, &(p_god->shit_list), (void *)p_god->threads) == ERROR_HARD)
		return (free (p_god->threads),free(p_god), NULL);
	p_god->forks = ft_calloc(p_god->num_of_philosophers, sizeof(pthread_mutex_t));
	if (!p_god->forks)
		return (free(p_god), NULL);
	if (add_to_shit_list(p_god, &(p_god->shit_list), (void *)p_god->forks) == ERROR_HARD)
		return (free (p_god->forks), free(p_god), NULL);
	print_p_init(p_god);
	return (p_god);
}

t_single_philo	*init_philo_struct(t_god_struct *p_god, int i)
{
	t_single_philo	*philo;

	philo = ft_calloc(1, sizeof(t_single_philo));
	if (!philo)
		return (NULL);
	if (add_to_shit_list(p_god, &(p_god->shit_list), philo) == ERROR_HARD)
		return (free(philo), NULL);
	philo->id = i;
	philo->no_o_t_e_p_m_eat = p_god->no_o_t_e_p_m_eat;
	philo->time_to_die = p_god->time_to_die;
	philo->time_to_eat = p_god->time_to_eat;
	philo->time_to_sleep = p_god->time_to_sleep;
	philo->time_since_last_meal = 0;
	philo->p_god = p_god;
	philo->status = INIT;
	assign_forks (p_god, philo);
	print_philo_forks(philo);
	return (philo);
}

void	init_mutexes(t_god_struct *p_god)
{
	int i;
	
	//pthread_mutex_init(&p_god->shit_mutex, NULL);
	pthread_mutex_init(&p_god->print_mutex, NULL);
	i = -1;
	while (++i < p_god->num_of_philosophers)
		pthread_mutex_init(&p_god->forks[i], NULL);
}
