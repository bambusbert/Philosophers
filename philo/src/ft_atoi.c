/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:51:49 by slambert          #+#    #+#             */
/*   Updated: 2026/05/17 21:03:28 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static char	*shift_whitespace(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	return (&nptr[i]);
}

int	ft_atoi(char *nptr)
{
	int			i;
	long long	num;

	if (!nptr)
		return (0);
	nptr = shift_whitespace(nptr);
	num = 0;
	i = 0;
	while (nptr[i])
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			break ;
		num *= 10;
		if (num > INT_MAX)
			return (ERROR_HARD);
		num += nptr[i] - 48;
		if (num > INT_MAX)
			return (ERROR_HARD);
		i++;
	}
	return ((int)num);
}
