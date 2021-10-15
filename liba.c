/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:48:24 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/15 10:25:30 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	int		i;

	i = 0;
	p = s;
	while (n-- > 0)
		p[i++] = '\0';
}

int	ft_atoi(const char *str)
{
	long long int	i;
	int				sign;
	long long int	number;
	long long int	cypher;

	i = 0;
	sign = 1;
	number = 0;
	cypher = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && cypher++ != -2)
		number = (number * 10) + (str[i++] - 48);
	if (cypher > 19)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (number * sign);
}

int	isnum(char *num)
{
	if (*num == '-' || *num == '+')
		num++;
	if (*num == '\0')
		return (3);
	while (*num >= '0' && *num <= '9')
		num++;
	if (*num != '\0')
		return (3);
	return (0);
}

uint64_t	getime(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (uint64_t)1000 + (tv.tv_usec / 1000));
}
