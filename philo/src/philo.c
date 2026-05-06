/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:25:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/06 15:25:02 by slambert         ###   ########.fr       */
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
		return (NULL);
	if (add_to_shit_list(p_god, &(p_god->shit_list), (void *)p_god->threads) == ERROR_HARD)
		return (free (p_god->threads), NULL);
	p_god->forks = ft_calloc(p_god->num_of_philosophers, sizeof(pthread_mutex_t));
	if (!p_god->forks)
		return (NULL);
	if (add_to_shit_list(p_god, &(p_god->shit_list), (void *)p_god->forks) == ERROR_HARD)
		return (free (p_god->forks), NULL);
	print_p_init(p_god);
	return (p_god);
}

int	start_simulation(t_god_struct *p_god)
{
	// printf("simulation started ")
	return (0);
}

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

void assign_forks(t_god_struct *p_god, t_single_philo *philo)
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

void	init_mutexes(t_god_struct *p_god)
{
	int i;
	
	//pthread_mutex_init(&p_god->shit_mutex, NULL);
	pthread_mutex_init(&p_god->print_mutex, NULL);
	i = -1;
	while (++i < p_god->num_of_philosophers)
		pthread_mutex_init(&p_god->forks[i], NULL);
}

void	destroy_mutexes(t_god_struct *p_god)
{
	int i;
	
	//pthread_mutex_destroy(&p_god->shit_mutex);
	pthread_mutex_destroy(&p_god->print_mutex);
		i = -1;
	while (++i < p_god->num_of_philosophers)
		pthread_mutex_destroy(&p_god->forks[i]);
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
