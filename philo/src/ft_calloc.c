/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:30:26 by slambert          #+#    #+#             */
/*   Updated: 2026/05/05 15:31:44 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

static int	multiplication_is_overflow(size_t n1, size_t n2)
{
	size_t	max_size;

	max_size = (size_t) -1;
	if (n1 == 0 || n2 == 0)
		return (0);
	if (n1 > max_size / n2)
		return (1);
	else
		return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			bytes;

	if (multiplication_is_overflow(nmemb, size))
		return (NULL);
	bytes = nmemb * size;
	ptr = (unsigned char *) malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bytes);
	return ((void *) ptr);
}

