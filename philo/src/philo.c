/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:25:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/24 14:40:29 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * THOUGHTS:
 * -    create a linked list with all the malloc'ed stuff. if I malloc smth,
 *      add it to that list. advantage: at the end or on error I just have to
 *      loop through that list and free everything.
 * -    (alternative to that): create a memory arena and recreate a malloc-style
 *      function (offset, returns pointer, can't fail blablabla)
 * -    after initialization I have to check wether the init process was
 *      successfull. If it was, that means that eachn philosopher is in a
 *      ready state
 */
#include "../inc/philo.h"

static int	one_philo_has_eaten_enough(t_single_philo *philo)
{
	if (get_times_eaten(philo) >= philo->no_o_t_e_p_m_eat)
		return (1);
	return (0);
}

static int	all_philos_have_eaten_enough(t_god_struct *p_god)
{
	t_single_philo	*cur_philo;

	if (p_god->no_o_t_e_p_m_eat == -1)
		return (0);
	cur_philo = p_god->philos;
	while (cur_philo)
	{
		if (!one_philo_has_eaten_enough(cur_philo))
			return (0);
		cur_philo = cur_philo->next;
	}
	return (1);
}

static void	initialize_start_time(t_god_struct *p_god)
{
	t_single_philo	*philo;

	p_god->start_time = return_time_in_ms();
	philo = p_god->philos;
	while (philo)
	{
		philo->time_last_meal = p_god->start_time;
		philo = philo->next;
	}
}

static void	monitor(t_god_struct *p_god)
{
	initialize_start_time(p_god);
	set_simul_ready(p_god);
	while (1)
	{
		if (all_philos_have_eaten_enough(p_god))
			set_end_simul(p_god);
		if (update_status_all(p_god) != -1)
			break ;
		if (get_end_simul(p_god) == 1)
			break ;
		usleep(500);
	}
	cleanup_everything(p_god);
}

int	main(int argc, char **argv)
{
	t_god_struct	*p_god;

	if (check_input(argc, argv) == ERROR_HARD)
		return (1);
	p_god = create_god_struct(argv);
	if (!p_god)
	{
		printf("malloc error in create_god_struct or argument INT_MAX "
			"overflow\n");
		cleanup_everything(p_god);
		return (1);
	}
	if (initialize_everything(p_god) == ERROR_HARD)
		return (1);
	monitor(p_god);
	return (0);
}
