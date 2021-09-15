/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:44:20 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/15 22:09:53 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(int argc, char **argv)
{
	printf("There's %d philosophers.\n", ft_atoi(argv[1]));
	printf("Sharing %d forks.\n", ft_atoi(argv[1]));
	printf("That will die if they don't eat after %d miliseconds. \n",
		ft_atoi(argv[2]));
	printf("Each one will eat for %d miliseconds.\n", ft_atoi(argv[3]));
	printf("And then sleep for another %d miliseconds\n", ft_atoi(argv[4]));
	if (argc == 6 && ft_atoi(argv[5]) > 0 && ft_atoi(argv[5]) < INT_MAX)
		printf("At least %d times.\n", ft_atoi(argv[5]));
	else
		printf("Till someone dies of sudden death or the hell freezes.\n");
}

void	check_num(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc && !(isnum(argv[i])))
		i++;
	if (i < argc)
		printf("Use numbers.\n");
	else
		check_args(argc, argv);
}

void	check_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		printf("Cambia el número de comensales...\n");
	else if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[2]) > INT_MAX)
	{
		printf("No está muerto lo que yace eternamente,");
		printf(" y con los evos extraños,");
		printf(" incluso la muerte puede morir\n");
	}
	else if (ft_atoi(argv[3]) < 60 || ft_atoi(argv[3]) > INT_MAX)
		printf("Comensales famélicos...\n");
	else if (ft_atoi(argv[4]) < 60 || ft_atoi(argv[4]) > INT_MAX)
		printf("Comensales insomnes...\n");
	else
		status(argc, argv);
}
