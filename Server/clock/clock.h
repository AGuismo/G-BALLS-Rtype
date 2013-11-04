#ifndef CLOCK_H_
# define CLOCK_H_

typedef struct	s_clock	t_clock;
typedef long long	clock_time;

# define	CLOCK_USEC	1000000.f
# define	CLOCK_MSEC	1000.f
# define	CLOCK_SEC	1.f

# define	CLOCK_PREC	CLOCK_USEC

typedef struct	s_gameclock
{
  t_clock	*header;
  void		(*start)(struct s_gameclock *clock);
  void		(*update)(struct s_gameclock *clock);
  clock_time	(*elapsed_time)(const struct s_gameclock *clock);
  clock_time	(*total_elapsed_time)(const struct s_gameclock *clock);
}		gameclock;

int		gameclock_ctor(gameclock *clock);
int		gameclock_dtor(gameclock *clock);

#endif /* CLOCK_H_ */
