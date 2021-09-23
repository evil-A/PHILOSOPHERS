/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:45:04 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/21 21:04:40 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_phila *p, char **argv)
{
	p->nphils = ft_atoi(argv[1]);
	p->forks = ft_atoi(argv[1]);
	p->tdie = ft_atoi(argv[2]);
	p->teat = ft_atoi(argv[3]);
	p->tslp = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (argv[5] <= 0)
			p->rounds = -1;
		else
			p->rounds = ft_atoi(argv[5]);
	}
//	p->nphils->f = malloc(pthread_t*);
}
/*	printf("%d %d %d %d %d %ld\n", p->nphils, p->nphils, p->tdie, p->teat, p->tslp, p->rounds);*/

static void	philer(t_phila *p, int i)
{
	p->lp[i].id = i + 1;
//	printf("philosopher id %d\n", p->lp[i].id);
	p->lp[i].state = THINK;
	p->lp[i].fork = i;
	p->lp[i].die = p->tdie;
}

static void	buildup(t_phila *p)
{
	int	i;

	p->lp = malloc(sizeof(t_phil) * p->nphils);
	i = 0;
	while (i < p->nphils)
	{
		ft_bzero(&p->lp[i], sizeof(t_phil));
		philer(p, i);
//		printf("philosopher %d\n", i + 1);
		i++;
	}
}

void	*sit(void *arg)
{
	int	id;

	id = *((int*)arg);
	printf("Philosofo %d se sienta a la mesa\n", id);
	return (NULL);
}

int	imprime(t_phila *p)
{
	int	i;

	i = 0;
	while (i < p->nphils)
	{
	//	printf("%d %d %d %d\n", p->lp[i].id, p->lp[i].state, p->lp[i].fork, p->lp[i].die);
		if (0 != pthread_create(&p->lp[i].f, NULL, sit, &p->lp[i].id))
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_phila	p;

	if (argc != 6 && argc != 5)
	{
		printf("Wrong number of arguments: %d\n", argc - 1);
		return (0);
	}
	if (check_num(argc, argv))
	{
		memset(&p, 0, sizeof(t_phila));
		setup(&p, argv);
		buildup(&p);
		imprime(&p);
	}
	return (0);
}
//   -lpthreads
// gcc XXXX -S  //crea codigo en ensamblador
/*Arguments
nphils number_of_philosophers
tdie time_to_die
teat time_to_eat
tslp time_to_sleep
rounds [number_of_times_each_philosopher_must_eat]

memset
printf
malloc
free
write
usleep
gettimeofday
pthread_create
pthread_detach
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock*/
