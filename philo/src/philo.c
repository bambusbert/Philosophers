/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:25:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/07 12:03:52 by slambert         ###   ########.fr       */
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
 * TODOs:
 * -	implement the sleep/think/eat cycle
 * -	add fork locking / unlocking
 * -	add death & time_to_eat monitoring
 * -	implement input validation
 * -	advance clanup.c & init.c error handling
 */
#include "../inc/philo.h"

/*
 *	TODO: check if args passed are valid (numeric, within certain limits
*	etc.). maybe in ft_atoi itself?
 *	if that's ok, we create the init_struct
 *
 */
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
	p_god->ready = 1;
	
	//here i have to somehow check if the simulation ended. that can happen
	//in 2 ways: 1. a philosopher has died. 2. a philosopher has eaten
	//time_to_eat times
	wait_for_philo_threads(p_god);
	cleanup_everything(p_god);
	return (0);
}
