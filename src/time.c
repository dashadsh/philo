

#include "../inc/philo.h"

// struct timeval {
//    time_t      tv_sec;   // Number of whole seconds of elapsed time
//    long int    tv_usec;  // Number of microseconds of rest of elapsed time minus tv_sec.
// }


// Returns the timestamp in milliseconds
   //1 sec = 1000000 microsecond
   //1 sec = 1000 millisec
   //1 millisec = 1000 microsec
   
long current_time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	//printf("%ld\n", t.tv_sec * 1000 + t.tv_usec / 1000);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}