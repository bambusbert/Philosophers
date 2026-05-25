/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:34:39 by slambert          #+#    #+#             */
/*   Updated: 2026/05/25 11:47:51 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	assign_forks(t_god_struct *p_god, t_single_philo *philo)
{
	if (philo->id == 0)
	{
		philo->fork_left = &p_god->forks[0];
		philo->fork_right = &p_god->forks[p_god->no_phil - 1];
		return ;
	}
	philo->fork_left = &p_god->forks[philo->id];
	philo->fork_right = &p_god->forks[philo->id - 1];
}

int	fill_args(t_god_struct *p_god, char **argv)
{
	p_god->no_phil = ft_atoi(argv[1]);
	if (p_god->no_phil == ERROR_HARD)
		return (ERROR_HARD);
	p_god->time_to_die = ft_atoi(argv[2]);
	if (p_god->time_to_die == ERROR_HARD)
		return (ERROR_HARD);
	p_god->time_to_eat = ft_atoi(argv[3]);
	if (p_god->time_to_eat == ERROR_HARD)
		return (ERROR_HARD);
	p_god->time_to_sleep = ft_atoi(argv[4]);
	if (p_god->time_to_sleep == ERROR_HARD)
		return (ERROR_HARD);
	if (argv[5])
	{
		p_god->no_o_t_e_p_m_eat = ft_atoi(argv[5]);
		if (p_god->no_o_t_e_p_m_eat == ERROR_HARD)
			return (ERROR_HARD);
	}
	else
		p_god->no_o_t_e_p_m_eat = -1;
	return (RET_OK);
}

t_god_struct	*create_god_struct(char **argv)
{
	t_god_struct	*p_god;

	p_god = ft_calloc(1, sizeof(t_god_struct));
	if (!p_god)
		return (NULL);
	if (fill_args(p_god, argv) == ERROR_HARD)
		return (free(p_god), NULL);
	p_god->shit_list = NULL;
	p_god->threads = ft_calloc(p_god->no_phil, sizeof(pthread_t));
	if (!p_god->threads)
		return (free(p_god), NULL);
	if (add_to_sl(&(p_god->shit_list), (void *)p_god->threads) == ERROR_HARD)
		return (free(p_god->threads), free(p_god), NULL);
	p_god->forks = ft_calloc(p_god->no_phil, sizeof(pthread_mutex_t));
	if (!p_god->forks)
		return (cleanup_shit_list(p_god->shit_list), free(p_god), NULL);
	if (add_to_sl(&(p_god->shit_list), (void *)p_god->forks) == ERROR_HARD)
		return (free(p_god->forks), cleanup_shit_list(p_god->shit_list),
			free(p_god), NULL);
	p_god->philos = NULL;
	p_god->ready = 0;
	p_god->simul_ended = 0;
	p_god->threads_created = 0;
	p_god->forks_initialized = 0;
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
	if (add_to_sl(&(p_god->shit_list), philo) == ERROR_HARD)
		return (free(philo), NULL);
	philo->id = i;
	philo->no_o_t_e_p_m_eat = p_god->no_o_t_e_p_m_eat;
	philo->time_to_die = p_god->time_to_die;
	philo->time_to_eat = p_god->time_to_eat;
	philo->time_to_sleep = p_god->time_to_sleep;
	philo->time_last_meal = p_god->start_time;
	philo->times_eaten = 0;
	philo->p_god = p_god;
	philo->status = INIT;
	assign_group(philo);
	assign_forks(p_god, philo);
	philo->next = NULL;
	if (init_philo_mutexes(philo) == ERROR_HARD)
		return (NULL);
	return (philo);
}
