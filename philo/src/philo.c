/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:25:09 by slambert          #+#    #+#             */
/*   Updated: 2026/05/04 16:33:38 by slambert         ###   ########.fr       */
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
 * -
 */
#include "../inc/philo.h"

int	start_simulation(t_god *p_init)
{
	return (0);
}

/* 
 *  The good thing about this is that you can exit the program from anywhere
 *  without having to bubble up exit codes or stuff like that. you just call
 *  cleanup_shit_list from anywhere and call exit
 *  TODO: think about if that is stupid??
 */
void cleanup_shit_list (t_shit_to_free *shit_list)
{
    t_shit_to_free *current;
    t_shit_to_free *next;
    
    current = shit_list;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int	add_to_shit_list(t_shit_to_free **shit_list, void *elem)
{
	t_shit_to_free	*new_node;
	t_shit_to_free	*current;

	new_node = malloc(sizeof(t_shit_to_free));
	if (!new_node)
	{
        printf("malloc error in add_to_shit_list\n");
        cleanup_shit_list(*shit_list);
        exit (1);
    }
	new_node->shit = elem;
	new_node->next = NULL;
	if (!*shit_list)
	{
		*shit_list = new_node;
		return (0);
	}
	current = *shit_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (0);
}

t_god	*init_simulation(char **argv, t_shit_to_free **shit_list)
{
	t_god	*p_init;

	p_init = malloc(sizeof(t_god));
	if (!p_init)
		return (NULL);
	p_init->num_of_philosophers = ft_atoi(argv[1]);
	p_init->time_to_die = ft_atoi(argv[2]);
	p_init->time_to_eat = ft_atoi(argv[3]);
	p_init->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p_init->no_o_t_e_p_m_eat = ft_atoi(argv[5]);
	else
		p_init->no_o_t_e_p_m_eat = -1;
	print_p_init(p_init);
	return (p_init);
}

int	main(int argc, char **argv)
{
	t_god	*p_init;
	t_shit_to_free	*shit_list;

	shit_list = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("wrong no. of args. use with 4 or 5 args\n");
		return (1);
	}
	// check if args passed are valid (numeric, within certain limits etc.)
	// if that's ok, we init the simulation
	p_init = init_simulation(argv, &shit_list);
	if (!p_init)
	{
		printf("malloc error in init_simulation\n");
		return (1);
	}
	start_simulation(p_init);
	// return something?
	return (0);
}
