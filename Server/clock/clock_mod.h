#ifndef CLOCK_MOD_H_
# define CLOCK_MOD_H_

# include	<sys/time.h>

typedef struct		s_clock
{
  struct timeval	last;
  float			elapsed_time;
  float			total_elapsed_time;
}			t_clock;

#endif /* CLOCK_MOD_H_ */
