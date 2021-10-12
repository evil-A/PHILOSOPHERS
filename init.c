/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:45:04 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/13 01:27:45 by evila-ro         ###   ########.fr       */
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
	if (argv[5])
	{
		if (argv[5] <= 0)
			p->rounds = -1;
		else
			p->rounds = ft_atoi(argv[5]);
	}
}

static void	philer(t_phila *p, int i)
{
	p->lp.id = i + 1;
//	printf("philosopher id %d\n", p->lp[i].id);
	p->lp.eat = p->teat;
	p->lp.sleep = p->tslp;
//	p->lp[i].fork = i;
	p->lp.die = p->tdie;
	if (p->rounds > 0)
		p->lp.ntimes = p->rounds;
	else
		p->lp.ntimes = -1;
	p->lp.froks = malloc(sizeof(pthread_mutex_t) * 2);
	/*
	p->froks = malloc(sizeof(pthread_mutex_t) * p->nphils);
	pthread_mutex_init(&p->froks[i], NULL);
	*/
	pthread_mutex_init(&p->lp.froks[1], NULL);//fadeout
	if (i != 0)// todos menos el primero
		p->lp.froks[0] = p->lp[i - 1].froks[1];
	if (p->lp.id == p->nphils)//el ultimo
		p->lp[0].froks[0] = p->lp[i].froks[1];
}

static void	buildup(t_phila **p)
{
	int	i;

	p->lp = malloc(sizeof(t_phil) * p->nphils);
	i = 0;
	while (i < p->nphils)
	{
		ft_bzero(&p->lp[i], sizeof(t_phil));
		philer(p, i);
		i++;
	}
}


void	*sit(void *arg)
{
	t_phil			*lp;
	
	lp = (t_phil*)arg;
	//printf("Philosofo %d se sienta a la mesa\n", lp->id);	
	while (1)
	{
		pthread_mutex_lock(&lp->froks[0]);
		pthread_mutex_lock(&lp->froks[1]);

		//int stamp = gettimeofday(struct timeval *restrict tp, void *restrict tzp);
//		printf("%I64d  el philosofo %d está comiendo\n", lp->id);
		usleep(lp->eat);

		pthread_mutex_unlock(&lp->froks[0]);
		pthread_mutex_unlock(&lp->froks[1]);

		printf("Tiempo el philosofo %d está durmiendo\n", lp->id);
		usleep(lp->sleep);
		printf("Tiempo el philosofo %d está pensando\n", lp->id);
		usleep((lp->die) - lp->eat + lp->sleep);
	}
	return (NULL);
}

int	imprime(t_phila **p)
{
	int	i;

	i = 0;
	while (i < p->nphils)
	{
		printf("Philosofo %d se sienta a la mesa\n", p->lp[i].id);
	//	printf("%d %d %d %d\n", p->lp[i].id, p->lp[i].state, p->lp[i].fork, p->lp[i].die);
		if (0 != pthread_create(&p->lp[i].f, NULL, sit, &p[i]))
	//	if (0 != pthread_create(&p->lp[i].f, NULL, ultrafuncion, &p))
			return (-1);
		p->pi = i;
		i++;
	}
	gettimeofday(&p->it, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", p->it.tv_sec, p->it.tv_usec);
	p->st = (p->it.tv_sec * 1000) + (p->it.tv_u>sec / 1000);
	i = 0;
	while (i < p->nphils)
		pthread_join(p->lp[i++].f, NULL);
	//p->it = gettimeofday(struct timeval *restrict tp, void *restrict tzp);

	return (0);
}

void	create(t_phila **p, char ** argv)
{
	int	i;

	i = 0;
	p = malloc(sizeof(t_phila *) * ft_atoi(argv[1] + 1));
	while (i < ft_atoi(argv[1]))
	{
		p[i] = malloc(sizeof(t_phila));
		ft_bzero(p[i], sizeof(t_phila));
		setup(p[i], argv);
		buildup(p[i]);
	}
}

int	main(int argc, char **argv)
{
	t_phila	**p;

	if (argc != 6 && argc != 5)
	{
		printf("Wrong number of arguments: %d\n", argc - 1);
		return (0);
	}
	if (check_num(argc, argv))
	{
		create(p, argv);

//		memset(&p, 0, sizeof(t_phila));
//		setup(&p, argv);
//		buildup(p);
		imprime(p);
	}
	return (0);
}
