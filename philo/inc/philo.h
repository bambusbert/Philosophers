/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:24:40 by slambert          #+#    #+#             */
/*   Updated: 2026/05/04 18:06:05 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_init_struct
{
	int						num_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						no_o_t_e_p_m_eat;
}							t_init_struct;

typedef struct s_shit_to_free
{
	void					*shit;
	struct s_shit_to_free	*next;
}							t_shit_to_free;

// struct for singular philosopher
typedef struct s_single_philo
{
	int						status;

	// info on left and right fork
}							t_single_philo;

enum						e_philo_status
{
	NOT_INIT = 0,
	INIT,
	SLEEPING,
	THINKING,
	HUNGRY,
	EATING,
	DEAD
};

void						print_p_init(t_init_struct *p_init);
int							ft_atoi(char *arg);

#endif