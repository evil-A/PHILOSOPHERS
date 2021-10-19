/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:29:39 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/19 09:50:59 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sit(void *arg)
{
	t_phil			*lp;

	lp = (t_phil *)arg;
	lp->death = getime() + lp->die;
	if (lp->id % 2)
		usleep(100);
	while (lp->ntimes != 0 && !lp->parent->the_end)
		even(lp);
	return (NULL);
}

void	alive(t_phila *p)
{
	int	i;

	while (!p->the_end && p->nobody)
	{
		i = 0;
		while (i < p->nphils)
		{
			if (getime() > p->lp[i].death)
			{
				p->the_end = 1;
				prontf(&p->lp[i], "ha muerto", 1);
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
		pthread_detach(p->lp[i].f);
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
	return (0);
}
