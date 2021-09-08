#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;
	int	cypher;

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
