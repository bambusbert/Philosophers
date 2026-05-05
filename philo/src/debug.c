/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:04:47 by slambert          #+#    #+#             */
/*   Updated: 2026/05/05 17:43:40 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_p_init(t_god_struct *p_init)
{
	printf("number of philosophers: %d\n", p_init->num_of_philosophers);
	printf("time to die: %d\n", p_init->time_to_die);
	printf("time to eat: %d\n", p_init->time_to_eat);
	printf("time to sleep: %d\n", p_init->time_to_sleep);
	if (p_init->no_o_t_e_p_m_eat > -1)
		printf("number of times each philosopher must eat: %d\n",
			p_init->no_o_t_e_p_m_eat);
}
