/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:51:49 by slambert          #+#    #+#             */
/*   Updated: 2026/05/15 19:56:17 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	sign_handler(const char *nptr)
{
	int	minus;
	int	was_there_a_sign;

	if (*nptr >= '0' && *nptr <= '9')
		return (0);
	was_there_a_sign = 0;
	minus = 0;
	if (nptr[0] == '-')
	{
		minus = 1;
		was_there_a_sign = 2;
	}
	else if (nptr[0] == '+')
	{
		was_there_a_sign = 2;
	}
	return (minus + was_there_a_sign);
}

static char	*shift_whitespace(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	return (&nptr[i]);
}

// TODO check if overflow safe
// TODO check if I have to check for negative numbers
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

/* int	ft_atoi(char *nptr)
{
	int			i;
	long long	num;
	int			minus;

	if (!nptr)
		return (0);
	nptr = shift_whitespace(nptr);
	minus = sign_handler(nptr);
	if (minus == -1)
		return (0);
	if (minus == 2 || minus == 3)
		nptr++;
	num = 0;
	i = 0;
	while (nptr[i])
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			break ;
		num *= 10;
		num += nptr[i] - 48;
		i++;
	}
	if (minus == 3)
		num *= (-1);
	return ((int)num);
} */
/* int	check_digit(long long *num, int neg, long long limit, char c)
{
	if (!neg && *num > (limit - (c - '0')) / 10)
		return (1);
	if (neg && *num < (limit + (c - '0')) / 10)
		return (1);
	if (!neg)
		*num = *num * 10 + (c - '0');
	else
		*num = *num * 10 - (c - '0');
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_overflow(char *arg)
{
	long long	num;
	long long	limit;
	int			neg;
	int			i;

	i = 0;
	neg = 0;
	num = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		neg = (arg[i++] == '-');
	if (neg)
		limit = LLONG_MIN;
	else
		limit = LLONG_MAX;
	while (ft_isdigit(arg[i]))
	{
		if (check_digit(&num, neg, limit, arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	set_is_num(char *arg)
{
	int	i;
	int	is_num;

	is_num = 1;
	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		is_num = 0;
	while (is_num && arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			while (arg[i] == ' ' || arg[i] == '\t')
				i++;
			if (arg[i] != '\0')
				is_num = 0;
			break ;
		}
		i++;
	}
	return (is_num);
} */