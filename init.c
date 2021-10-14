/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:29:39 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/14 08:53:20 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_phila *p, int i, char **argv)
{
	p[i].nphils = ft_atoi(argv[1]);
//	p[i].forks = ft_atoi(argv[1]);
	p[i].tdie = ft_atoi(argv[2]);
	p[i].teat = ft_atoi(argv[3]);
	p[i].tslp = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (argv[5] == 0)
			p[i].rounds = -1;
		else
			p[i].rounds = ft_atoi(argv[5]);
	}
}

static void	philer(t_phila *p, int i)
{
	p[i].lp.id = i + 1;
	p[i].lp.eat = p[i].teat * 1000;
	p[i].lp.sleep = p[i].tslp * 1000;
	p[i].lp.die = p[i].tdie * 1000;
	if (p[i].rounds > 0)
		p[i].lp.ntimes = p[i].rounds;
	else
		p[i].lp.ntimes = -1;
	p[i].lp.froks = malloc(sizeof(pthread_mutex_t) * 2);
	p[i].lp.ross = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&p[i].lp.froks[1], NULL);
	pthread_mutex_init(p[i].lp.ross, NULL);
	if (i != 0)// todos menos el primero
		p[i].lp.froks[0] = p[i - 1].lp.froks[1];
	if (p[i].lp.id == p[i].nphils)//el ultimo
		p[0].lp.froks[0] = p[i].lp.froks[1];
}

void	prontf(t_phila *p, char *str)
{
	pthread_mutex_lock(p->lp.ross);
//	printf("XXXXX %04llu\n", (uint64_t)p->st);
	gettimeofday(&p->it, NULL);
	p->nt = mili(p->it.tv_sec, p->it.tv_usec);
	p->zt = p->nt - p->st;
//	printf("start %04llu now %04llu resta %04llu\n", p->st, p->nt, p->zt);
	printf("%04llu El filósofo %d %s\n", p->zt, p->lp.id, str);
	pthread_mutex_unlock(p->lp.ross);
	
}
/*
int nosleep(t_phila *p, int time)
{
	uint64_t	i;

	i = 0;
	while ((p->st + i) < (p->st + time))
		i++;
}
*/
void	*sit(void *arg)
{
	t_phila			*p;
	
	p = (t_phila*)arg;
	//printf("Philosofo %d se sienta a la mesa\n", lp->id);	
	while (1)
	{
		if (p->lp.id % 2 == 0)
		{
			pthread_mutex_lock(&p->lp.froks[0]);
			prontf(p, "coje el tenedor izquierdo.");
			pthread_mutex_lock(&p->lp.froks[1]);
			prontf(p, "coje el tenedor derecho.");
			prontf(p, "empieza a comer.");
			usleep(p->lp.eat);//reloj del sistema
			prontf(p, "deja de comer.");
		}
		else
		{
			pthread_mutex_lock(&p->lp.froks[1]);
			prontf(p, "coje el tenedor derecho.");
			pthread_mutex_lock(&p->lp.froks[0]);
			prontf(p, "coje el tenedor izquierdo.");
			prontf(p, "empieza a comer.");
			usleep(p->lp.eat);//reloj del sistema
			prontf(p, "deja de comer.");

		}	
			pthread_mutex_unlock(&p->lp.froks[0]);
			pthread_mutex_unlock(&p->lp.froks[1]);

			prontf(p, "está durmiendo");
			usleep(p->lp.sleep);
			prontf(p, "está pensando");
			usleep((p->lp.die) - p->lp.eat + p->lp.sleep);
	}
	return (NULL);
}

int	imprime(t_phila *p)
{
	int				i;
	struct timeval	zod;
	
	gettimeofday(&zod, NULL);
	i = 0;
	while (i < p[i].nphils)
	{
	//	printf("Philosofo %d se sienta a la mesa\n", p[i].lp.id);
	//	printf("%d %d %d %d\n", p->lp[i].id, p->lp[i].state, p->lp[i].fork, p->lp[i].die);
		if (0 != pthread_create(&p[i].lp.f, NULL, sit, &p[i]))
	//	if (0 != pthread_create(&p->lp[i].f, NULL, ultrafuncion, &p))
			return (-1);
		p[i].pi = i;
//		gettimeofday(&p[i].it, NULL);
//		p[i].st = mili(p[i].it.tv_sec, p[i].it.tv_usec);
		p[i].st = mili(zod.tv_sec, zod.tv_usec);
		printf("seconds : %ld\nmicro seconds : %d\n", (zod.tv_sec), (zod.tv_usec));
//		printf("seconds : %ld\nmicro seconds : %d\n", (p[i].it.tv_sec), (p[i].it.tv_usec));
		printf("%04llu\n", p[i].st);
		i++;
	}
//	gettimeofday(&p[i].it, NULL);
//	p[i].st = mili(p[i].it.tv_sec, p[i].it.tv_usec);
//	printf("seconds : %ld\nmicro seconds : %d\n", (p[i].it.tv_sec), (p[i].it.tv_usec));
//	printf("%04llu\n", p[i].st);
	i = 0;
	while (i < p[i].nphils)
		pthread_join(p[i++].lp.f, NULL);

	return (0);
}

void	create(t_phila *p, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
//		printf("%d\n", i);
//		p[i]->lp = *(t_phil *)malloc(sizeof(t_phil));
//		p[i] = malloc(sizeof(t_phila));
//		exit (0);
		//ft_bzero(p[i], sizeof(t_phila));
		setup(p, i, argv);
//		buildup(p[i], i);
		philer(p, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_phila	*p;

	if (argc != 6 && argc != 5)
	{
		printf("Wrong number of arguments: %d\n", argc - 1);
		return (0);
	}
	if (check_num(argc, argv))
	{
		p = malloc(sizeof(t_phila) * (ft_atoi(argv[1]) + 1));
		create(p, argv);

//		memset(p, 0, sizeof(t_phila));
//		setup(p, argv);
//		buildup(p);
		imprime(p);
	}
	return (0);
}
