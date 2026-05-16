/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:31:28 by slambert          #+#    #+#             */
/*   Updated: 2026/05/16 18:39:35 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	input_not_numeric(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (ERROR_HARD);
			j++;
		}
		i++;
	}
	return (RET_OK);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong no. of args. use with 4 or 5 args\n");
		return (ERROR_HARD);
	}
	if (input_not_numeric(argc, argv) == ERROR_HARD)
	{
		printf("non-numeric input detected\n");
		return (ERROR_HARD);
	}
	return (RET_OK);
}

int	zero_check(t_god_struct *p_god)
{
	if (p_god->no_phil == 0
		|| p_god->time_to_die == 0
		|| p_god->time_to_eat == 0
		|| p_god->time_to_sleep == 0
		|| p_god->no_o_t_e_p_m_eat == 0)
	{
		return (ERROR_HARD);
	}
	return (RET_OK);
}
