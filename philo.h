/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:49:19 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/15 10:25:27 by evila-ro         ###   ########.fr       */
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

# define DEAD 0
# define EAT 1
# define SLEEP 2
# define THINK 3

struct s_phila;

typedef struct s_phil
{
	pthread_t	f;
	int			id;
	int			state;
//	int			fork;
	pthread_mutex_t			*fr;
	pthread_mutex_t			*fl;
//	pthread_mutex_t			*ross;
	int			die;
	int			eat;
	int			sleep;
	int			ntimes;
	int			dish;
	struct s_phila	*parent;
}				t_phil;

/*typedef struct s_rush
{
	pthread_mutex_t			*ross;
	uint64_t				st;
	uint64_t				nt;
	uint64_t				zt;
	struct timeval			it;
}				t_rush;
*/

typedef struct s_phila
{
	int						nphils;
//	pthread_mutex_t			*froks;
	int						tdie;
	int						teat;
	int						tslp;
//	int						pi;
	long int				rounds;
	uint64_t				st;
//	uint64_t				nt;
//	uint64_t				zt;
//	struct timeval			it;
	pthread_mutex_t			ross;
	t_phil					*lp;
}				t_phila;

int			main(int argc, char **argv);
void		setup(t_phila *phil, char **argv);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			isnum(char *num);
uint64_t	getime();
int			check_args(int argc, char **argv);
int			check_num(int argc, char **argv);
int			status(int argc, char **argv);

#endif
