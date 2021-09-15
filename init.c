/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:45:04 by evila-ro          #+#    #+#             */
/*   Updated: 2021/09/15 22:16:45 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup(t_philo phil, char **argv)
{
	phil.nphils = ft_atoi(argv[1]);
	phil.nphils = ft_atoi(argv[1]);
	phil.tdie = ft_atoi(argv[2]);
	phil.teat = ft_atoi(argv[3]);
	phil.tslp = ft_atoi(argv[4]);
	if (argv[5])
		phil.rounds = ft_atoi(argv[5]);
	printf("%d %d %d %d %d %ld\n", phil.nphils, phil.nphils, phil.tdie, phil.teat, phil.tslp, phil.rounds);
}

int	main(int argc, char **argv)
{
	t_philo	phil;

	if (argc != 6 && argc != 5)
	{
		printf("Wrong number of arguments: %d\n", argc - 1);
		return (0);
	}
	check_num(argc, argv);
	memset(&phil, 0, sizeof(t_philo));
	setup(phil, argv);
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
