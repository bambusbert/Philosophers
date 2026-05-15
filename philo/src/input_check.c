/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:31:28 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:47:03 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	input_not_numeric(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < 5)
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
	if (input_not_numeric(argv) == ERROR_HARD)
	{
		printf("non-numeric input detected\n");
		return (ERROR_HARD);
	}
	return (RET_OK);
}
