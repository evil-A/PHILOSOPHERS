/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:48:24 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/15 22:18:28 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long int	i;
	int				sign;
	long long int	number;
	long long int				cypher;

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
