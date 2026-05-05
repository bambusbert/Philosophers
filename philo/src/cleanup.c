/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:33:42 by slambert          #+#    #+#             */
/*   Updated: 2026/05/05 16:34:29 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* 
 *  The good thing about this is that you can exit the program from anywhere
 *  without having to bubble up exit codes or stuff like that. you just call
 *  cleanup_shit_list from anywhere and call exit
 *  TODO: think about if that is stupid??
 */
static void cleanup_shit_list (t_shit_to_free *shit_list)
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

void cleanup_and_exit (t_god_struct *p_god, int i)
{
	cleanup_shit_list(p_god->shit_list);
	free (p_god);
	exit(i);
}

/*
 *	be careful! the god list is the only malloc'ed thing that is NOT
 *	a member of the shit list
 */
int	add_to_shit_list(t_shit_to_free **shit_list, void *elem)
{
	t_shit_to_free	*new_node;
	t_shit_to_free	*current;

	new_node = ft_calloc(1, sizeof(t_shit_to_free));
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
