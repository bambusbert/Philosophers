/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:33:42 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 12:17:53 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 *  The good thing about this is that you can exit the program from anywhere
 *  without having to bubble up exit codes or stuff like that. you just call
 *  cleanup_shit_list from anywhere and call exit
 *  TODO: think about if that is stupid??
 * 	problem: wxit is not allowed (only in bonus)
 */
static void	cleanup_shit_list(t_shit_to_free *shit_list)
{
	t_shit_to_free	*current;
	t_shit_to_free	*next;

	current = shit_list;
	while (current)
	{
		next = current->next;
		free(current->shit);
		free(current);
		current = next;
	}
}

/*
 *	be careful! the god list is the only malloc'ed thing that is NOT
 *	a member of the shit list
 */
int	add_to_shit_list(t_god_struct *p_god, t_shit_to_free **shit_list,
		void *elem)
{
    t_shit_to_free	*new_node;
	t_shit_to_free	*current;
    
	//pthread_mutex_lock(&p_god->shit_mutex);
	new_node = ft_calloc(1, sizeof(t_shit_to_free));
	if (!new_node)
	{
		//pthread_mutex_unlock(&p_god->shit_mutex);
		printf("malloc error in add_to_shit_list\n");
		return ERROR_HARD;
	}
	new_node->shit = elem;
	new_node->next = NULL;
	if (!*shit_list)
	{
		*shit_list = new_node;
		//pthread_mutex_unlock(&p_god->shit_mutex);
		return (0);
	}
	current = *shit_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	//pthread_mutex_unlock(&p_god->shit_mutex);
	return (0);
}

void	destroy_philo_mutexes(t_god_struct *p_god)
{
	t_single_philo *cur_philo;

	cur_philo = p_god->philos;
	while (cur_philo)
	{
		pthread_mutex_destroy(&cur_philo->time_last_meal_mutex);
		pthread_mutex_destroy(&cur_philo->times_eaten_mutex);
		cur_philo = cur_philo->next;
	}
}

void	destroy_global_mutexes(t_god_struct *p_god)
{
	int i;
	
	pthread_mutex_destroy(&p_god->simul_ready_mutex);
	pthread_mutex_destroy(&p_god->print_mutex);
	i = -1;
	while (++i < p_god->num_of_philosophers)
		pthread_mutex_destroy(&p_god->forks[i]);
	pthread_mutex_destroy(&p_god->simul_ended_mutex);
	pthread_mutex_destroy(&p_god->philo_add_mutex);
}

void	cleanup_everything(t_god_struct *p_god)
{
	cleanup_shit_list(p_god->shit_list);
    destroy_global_mutexes(p_god);
	destroy_philo_mutexes (p_god);
	free(p_god);
}

//unfortunately exit is not allowed, only in the bonus :(
/* void cleanup_and_exit (t_god_struct *p_god, int i)
{
	t_shit_to_free	*new_node;
	t_shit_to_free	*current;

	cleanup_shit_list(p_god->shit_list);
	free (p_god);
	exit(i);
} */