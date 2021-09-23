/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:49:19 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/21 21:04:35 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <strings.h>
# include <stdlib.h>
# define DEAD 0
# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_phil
{
	pthread_t	f;
	int			id;
	int			state;
	int			fork;
	int			die;
}				t_phil;

typedef struct s_phila
{
	int			nphils;
	int			forks;
	int			tdie;
	int			teat;
	int			tslp;
	long int	rounds;
	t_phil		*lp;
}				t_phila;

int		main(int argc, char **argv);
void	setup(t_phila *phil, char **argv);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		isnum(char *num);
int		check_args(int argc, char **argv);
int		check_num(int argc, char **argv);
int		status(int argc, char **argv);

#endif
