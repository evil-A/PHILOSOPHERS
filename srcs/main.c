#include "philo.h"

int main(int argc, char **argv)
{
	if (argc != 6)
	{
		printf("Wrong number of arguments: %d\n", argc);
		return (0);
	}
	check_args(argv);
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
