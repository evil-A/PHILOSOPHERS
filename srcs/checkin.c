#include "philo.h"

void	check_args(char **argv)
{
	if (ft_atoi(argv[1]) < 1)
		printf("Pocos comensales...\n");
	if (ft_atoi(argv[2]) < 1)
		printf("No está muerto lo que yace eternamente, y con los evos extraños, incluso la muerte puede morir\n");
	if (ft_atoi(argv[3]) < 1)
		printf("Comensales famélicos...\n");
	if (ft_atoi(argv[4]) < 1)
		printf("Comensales insomnes...\n");
	if (ft_atoi(argv[5]) < 1)
		printf("muerte subita\n");//configurar
}
