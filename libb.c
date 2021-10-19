/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 09:48:47 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/19 09:53:24 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_phila *p, char **argv)
{
	p->nphils = ft_atoi(argv[1]);
	p->nobody = p->nphils;
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

void	philer(t_phil *lp, int i)
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
	lp->parent->nobody -= (lp->ntimes == 0);
	prontf(lp, "está durmiendo", 0);
	nosleep(lp->sleep);
	prontf(lp, "está pensando", 0);
}
