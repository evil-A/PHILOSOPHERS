/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:49:19 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/18 11:05:04 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>

struct	s_phila;

typedef struct s_phil
{
	pthread_t		f;
	int				id;
	int				state;
	pthread_mutex_t	*fr;
	pthread_mutex_t	*fl;
	uint64_t		death;
	uint64_t		die;
	int				eat;
	int				sleep;
	int				ntimes;
	int				dish;
	struct s_phila	*parent;
}				t_phil;

typedef struct s_phila
{
	int						nphils;
	int						tdie;
	int						teat;
	int						tslp;
	int						the_end;
	long int				rounds;
	uint64_t				st;
	pthread_mutex_t			ross;
	t_phil					*lp;
}				t_phila;

int			main(int argc, char **argv);
void		setup(t_phila *phil, char **argv);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			isnum(char *num);
uint64_t	getime(void);
int			check_args(int argc, char **argv);
int			check_num(int argc, char **argv);
int			status(int argc, char **argv);

#endif
