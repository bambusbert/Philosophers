/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:25:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 15:36:52 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO exit is not allowed! only in bonus :(

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
 * -
 */
#include "../inc/philo.h"

// thats the function that gets spawned by a philo thread
void	*philo_routine(void *arg)
{
	t_single_philo	*philo;

	philo = (t_single_philo *)arg;
	pthread_mutex_lock(&philo->p_god->print_mutex);
	//printf("Philosopher %d is ready\n", philo->id);
	pthread_mutex_unlock(&philo->p_god->print_mutex);
	return ((void *)NULL);
}

/*
 *	1. initialize the philo struct
 *	2. start the philo thread with that struct as the argument
 */
int	create_philo_thread(t_god_struct *p_god, int i)
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

int	main(int argc, char **argv)
{
	t_god_struct	*p_god;
	t_shit_to_free	*shit_list;

	shit_list = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("wrong no. of args. use with 4 or 5 args\n");
		return (1);
	}
	// check if args passed are valid (numeric, within certain limits etc.)
	// maybe in ft_atoi itself?
	// if that's ok, we create the init_struct
	p_god = create_god_struct(argv);
	if (!p_god)
	{
		printf("malloc error in create_god_struct\n");
		cleanup_everything(p_god);
		return (1);
	}
	init_mutexes(p_god);
	if (create_philo_threads(p_god) == ERROR_HARD)
	{
		printf("critical error in create_philo_threads\n");
		cleanup_everything(p_god);
		return (1);
	}
	
	wait_for_philo_threads(p_god);
	cleanup_everything(p_god);
	return (0);
}
