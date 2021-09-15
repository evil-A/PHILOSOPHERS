/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:49:19 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/15 22:16:14 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <strings.h>

typedef struct s_philo
{
	int	nphils;
	int	forks;
	int	tdie;
	int	teat;
	int	tslp;
	long int	rounds;
}				t_philo;

int		main(int argc, char **argv);
void	setup(t_philo phil, char **argv);
int		ft_atoi(const char *str);
int		isnum(char *num);
void	check_args(int argc, char **argv);
void	check_num(int argc, char **argv);
void	status(int argc, char **argv);

#endif
