/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:34:39 by slambert          #+#    #+#             */
/*   Updated: 2026/05/07 12:29:22 by slambert         ###   ########.fr       */
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

void fill_args(t_god_struct *p_god, char **argv)
{
	p_god->num_of_philosophers = ft_atoi(argv[1]);
	p_god->time_to_die = ft_atoi(argv[2]);
	p_god->time_to_eat = ft_atoi(argv[3]);
	p_god->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p_god->no_o_t_e_p_m_eat = ft_atoi(argv[5]);
	else
		p_god->no_o_t_e_p_m_eat = -1;
}

t_god_struct	*create_god_struct(char **argv)
{
	t_god_struct	*p_god;

	p_god = ft_calloc(1, sizeof(t_god_struct));
	if (!p_god)
		return (NULL);
	fill_args(p_god, argv);
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
	p_god->start_time = return_time_in_ms();
	p_god->ready = 0;
	//print_p_init(p_god);
	return (p_god);
}

void	assign_group(t_single_philo *philo)
{
	if (philo->id % 2 == 0)
		philo->group = GROUP_EVEN;
	else
		philo->group = GROUP_ODD;
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
	philo->last_meal_time = p_god->start_time;
	philo->times_eaten = 0;
	philo->is_alternating = 0;
	philo->p_god = p_god;
	philo->status = INIT;
	if (i == p_god->num_of_philosophers - 1 && philo->id % 2 == 0)
		philo->is_alternating = 1;
	assign_group(philo);
	assign_forks (p_god, philo);
	//print_philo_forks(philo);
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
	pthread_mutex_init(&p_god->philo_dead, NULL);
}
