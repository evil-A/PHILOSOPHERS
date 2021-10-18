/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:29:39 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/18 12:15:54 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_phila *p, char **argv)
{
	p->nphils = ft_atoi(argv[1]);
	p->tdie = ft_atoi(argv[2]);
	p->teat = ft_atoi(argv[3]);
	p->tslp = ft_atoi(argv[4]);
	p->st = getime();
	p->the_end = 0;
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
	lp[i].id = i + 1;
	lp[i].eat = lp->parent->teat;
	lp[i].sleep = lp->parent->tslp;
	lp[i].die = lp->parent->tdie;
	if (lp[i].parent->rounds > 0)
		lp[i].ntimes = lp->parent->rounds;
	else
		lp[i].ntimes = -1;
	lp[i].fr = malloc(sizeof(pthread_mutex_t));
	if (!lp[i].fr)
		return ;
	pthread_mutex_init(lp[i].fr, NULL);
	if (i != 0)
		lp[i].fl = lp[i - 1].fr;
	if (i == lp->parent->nphils - 1)
		lp[0].fl = lp[i].fr;
}

void	prontf(t_phil *lp, char *str, int force)
{
	uint64_t	zt;

	if (!lp->parent->the_end || force)
	{
		pthread_mutex_lock(&lp->parent->ross);
		zt = getime() - lp->parent->st;
		printf("%04llu El filósofo %d %s\n", zt, lp->id, str);
		pthread_mutex_unlock(&lp->parent->ross);
	}
}

void	nosleep(uint64_t msec)
{
	uint64_t	diff;

	diff = getime() + msec;
	while (diff > getime())
		usleep(500);
}

void	even(t_phil *lp)
{
	pthread_mutex_lock(lp->fr);
	prontf(lp, "coje el tenedor derecho.", 0);
	pthread_mutex_lock(lp->fl);
	prontf(lp, "coge el tenedor izquierdo.", 0);
	prontf(lp, "está comiendo.", 0);
	lp->death = getime() + lp->die;
	nosleep(lp->eat);
	pthread_mutex_unlock(lp->fr);
	pthread_mutex_unlock(lp->fl);
	lp->ntimes--;
	prontf(lp, "está durmiendo", 0);
	nosleep(lp->sleep);
	prontf(lp, "está pensando", 0);
}

void	odd(t_phil *lp)
{
	pthread_mutex_lock(lp->fl);
	prontf(lp, "coje el tenedor izquierdo.", 0);
	pthread_mutex_lock(lp->fr);
	prontf(lp, "coge el tenedor derecho.", 0);
	prontf(lp, "está comiendo.", 0);
	lp->death = getime() + lp->die;
	nosleep(lp->eat);
	pthread_mutex_unlock(lp->fl);
	pthread_mutex_unlock(lp->fr);
	lp->ntimes--;
	prontf(lp, "está durmiendo", 0);
	nosleep(lp->sleep);
	prontf(lp, "está pensando", 0);
}

void	*sit(void *arg)
{
	t_phil			*lp;

	lp = (t_phil *)arg;
	lp->death = getime() + lp->die;
	if (lp->id % 2)
		usleep(100);
	while (lp->ntimes != 0 && !lp->parent->the_end)
	{
//		if (lp->id % 2 == 0)
			even(lp);
//		else
//			odd(lp);
	}
	return (NULL);
}

void	alive(t_phila *p)
{
	int	i;
	int	nobody_need_eat;

	nobody_need_eat = p->nphils;
	while (!p->the_end && nobody_need_eat)
	{
		i = 0;
// Todos han de comer un numero de veces y entonces termina el programa.
//		if (p->lp[i].ntimes == 0)
//			break ;
//
		while (i < p->nphils)
		{
			nobody_need_eat -= (p->lp[i].ntimes == 0);
			if (getime() > p->lp[i].death)
			{
				p->the_end = 1;
				prontf(&p->lp[i], "ha muerto", 1);
//				printf("%04llu El philosofo %d ha muerto.\n",
//					getime() - p->st, p->lp[i].id);
//				printf("!Viva el simio!\n");
//				pthread_detach(p->lp[i].f);
				break ;
			}
			i++;
		}
	}
}

int	loopi(t_phila *p)
{
	int				i;

	i = 0;
	while (i < p->nphils)
	{
		if (0 != pthread_create(&p->lp[i].f, NULL, sit, p->lp + i))
			return (-1);
	//	pthread_detach(p->lp[i].f);
		i++;
	}
	alive(p);
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
		p->lp[i].parent = p;
		philer(p->lp, i);
		i++;
	}
}
void	freedom(t_phila *p)
{
	int	i;

//	pthread_mutex_destroy(&p->ross);
	i = 0;
	while (i < p->nphils)
	{
		pthread_mutex_destroy(p->lp[i].fr);
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
		create(&p, argv);
		loopi(&p);
	}
	freedom(&p);
//	system("leaks philo");
	return (0);
}
