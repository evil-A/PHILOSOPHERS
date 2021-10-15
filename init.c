/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:29:39 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/15 10:25:24 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_phila *p, char **argv)
{
	p->nphils = ft_atoi(argv[1]);
//	p->forks = ft_atoi(argv[1]);
	p->tdie = ft_atoi(argv[2]);
	p->teat = ft_atoi(argv[3]);
	p->tslp = ft_atoi(argv[4]);
	p->st = getime();
	if (argv[5])
	{
		if (argv[5] == 0)
			p->rounds = -1;
		else
			p->rounds = ft_atoi(argv[5]);
	}
}

static void	philer(t_phil *lp, int i)
{
//	static t_rush	*rush;

	lp[i].id = i + 1;
	lp[i].eat = lp->parent->teat;
	lp[i].sleep = lp->parent->tslp;
	lp[i].die = lp->parent->tdie;
	if (lp[i].parent->rounds > 0)
		lp[i].ntimes = lp->parent->rounds;
	else
		lp[i].ntimes = -1;
//	if (!rush)
//		rush = malloc(sizeof(t_rush));
	lp[i].fr = malloc(sizeof(pthread_mutex_t));
	if (!lp[i].fr)
		return ;
//	lp->fl = malloc(sizeof(pthread_mutex_t));
//	rush->ross = malloc(sizeof(pthread_mutex_t));
//	p[i].lp.ross = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(lp[i].fr, NULL);
//	pthread_mutex_init(&lp->fl, NULL);
//	pthread_mutex_init(rush->ross, NULL);
//	pthread_mutex_init(p[i].lp.ross, NULL);
//	rush = rush;
	if (i != 0)// todos menos el primero
		lp[i].fl = lp[i - 1].fr;
	if (i == lp->parent->nphils - 1)//el ultimo
		lp[0].fl = lp[i].fr;
}

void	prontf(t_phil *lp, char *str)
{
	uint64_t	zt;
	pthread_mutex_lock(&lp->parent->ross);
//	printf("XXXXX %04llu\n", (uint64_t)p->st);
//	lp->parent->nt = mili(lp->it.tv_sec, lp->it.tv_usec);
//	lp->zt = lp->nt - lp->st;
//	printf("RUSH %p\n", p->rush);
	zt = getime() - lp->parent->st;
//	printf("%04llu\n", p[i].st);
//	printf("start %04llu now %04llu resta %04llu\n", p->st, p->nt, p->zt);
	printf("%04llu El filósofo %d %s\n", zt, lp->id, str);
	pthread_mutex_unlock(&lp->parent->ross);
	
}

void nosleep(uint64_t msec)
{
	uint64_t	diff;

	diff = getime() + msec; 
	while (diff > getime())
		usleep(500);
}

void	*sit(void *arg)
{
	t_phil			*lp;
	
	lp = (t_phil*)arg;
	//printf("Philosofo %d se sienta a la mesa\n", lp->id);	
	while (1)
	{
		if (lp->id % 2 == 0)
		{
			pthread_mutex_lock(lp->fr);
			prontf(lp, "coje el tenedor izquierdo.");
			pthread_mutex_lock(lp->fl);
			prontf(lp, "coje el tenedor derecho.");
			prontf(lp, "empieza a comer.");
			nosleep(lp->eat);//reloj del sistema
			prontf(lp, "deja de comer.");
		}
		else
		{
			pthread_mutex_lock(lp->fl);
			prontf(lp, "coje el tenedor derecho.");
			pthread_mutex_lock(lp->fr);
			prontf(lp, "coje el tenedor izquierdo.");
			prontf(lp, "empieza a comer.");
			nosleep(lp->eat);//reloj del sistema
			prontf(lp, "deja de comer.");

		}	
			pthread_mutex_unlock(lp->fr);
			pthread_mutex_unlock(lp->fl);

			prontf(lp, "está durmiendo");
			nosleep(lp->sleep);
			prontf(lp, "está pensando");
			nosleep((lp->die) - lp->eat + lp->sleep);
	}
	return (NULL);
}

int	imprime(t_phila *p)
{
	int				i;
//	struct timeval	zod;
	
//	gettimeofday(&zod, NULL);
	i = 0;
	while (i < p->nphils)
	{
	//	printf("Philosofo %d se sienta a la mesa\n", p[i].lp.id);
	//	printf("%d %d %d %d\n", p->lp[i].id, p->lp[i].state, p->lp[i].fork, p->lp[i].die);
		if (0 != pthread_create(&p->lp[i].f, NULL, sit, p->lp + i))
			return (-1);
//		p->lp[i].pi = i;
//		gettimeofday(&p[i].it, NULL);
//		p[i].st = mili(p[i].it.tv_sec, p[i].it.tv_usec);
//		printf("seconds : %ld\nmicro seconds : %d\n", (zod.tv_sec), (zod.tv_usec));
//		printf("seconds : %ld\nmicro seconds : %d\n", (p[i].it.tv_sec), (p[i].it.tv_usec));
//		printf("%04llu\n", p->st);
		i++;
	}
	// bucle mortal
	// tiempo actual mas tiempo de reseteo
	// variable silence hablan todos o nadie
	i = 0;
	while (i < p->nphils)
		pthread_join(p->lp[i++].f, NULL);

	return (0);
}

void	create(t_phila *p, char **argv)
{
	int	i;

	setup(p, argv);
	i = 0;
	while (i < p->nphils)
	{
//		printf("%d\n", i);
//		p[i]->lp = *(t_phil *)malloc(sizeof(t_phil));
//		p[i] = malloc(sizeof(t_phil));
//		exit (0);
		//ft_bzero(p[i], sizeof(t_phila));
//		buildup(p[i], i);
		p->lp[i].parent = p;
		philer(p->lp, i);
		i++;
	}
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
		p.lp = malloc(sizeof(t_phil) * (ft_atoi(argv[1])));
//		printf("num fil %lu\n", sizeof(t_phil));
		create(&p, argv);

//		memset(&p, 0, sizeof(t_phila));
//		setup(&p, argv);
//		buildup(&p);
		imprime(&p);
	}
	return (0);
}
