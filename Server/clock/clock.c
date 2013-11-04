#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"clock.h"
#include	"clock_mod.h"
#include	"error.h"

static void		_start(struct s_gameclock *clock);
static void		_update(struct s_gameclock *clock);
static clock_time	_elapsed_time(const struct s_gameclock *clock);
static clock_time	_total_elapsed_time(const struct s_gameclock *clock);

int			gameclock_ctor(gameclock *clock)
{
  ((clock->header = calloc(1, sizeof(*clock->header))) == NULL) ?
    error("Unable to initialize gameclock");
  gettimeofday(&clock->header->last, NULL);
  clock->start = &_start;
  clock->update = &_update;
  clock->elapsed_time = &_elapsed_time;
  clock->total_elapsed_time = &_total_elapsed_time;
  return (0);
}

int			gameclock_dtor(gameclock *clock)
{
  free(clock->header);
  return (0);
}

static void		_start(struct s_gameclock *clock)
{
  gettimeofday(&clock->header->last, NULL);
}

static void		_update(struct s_gameclock *clock)
{
  struct timeval	current;
  struct timeval	*prev;
  float			elapsed_time;

  prev = &clock->header->last;
  gettimeofday(&current, NULL);
  elapsed_time = (current.tv_sec - prev->tv_sec) * CLOCK_PREC;
  elapsed_time += (current.tv_usec - prev->tv_usec);
  *prev = current;
  clock->header->elapsed_time = elapsed_time;
  clock->header->total_elapsed_time += elapsed_time;
}

static clock_time	_elapsed_time(const struct s_gameclock *clock)
{
  return (clock->header->elapsed_time);
}

static clock_time	_total_elapsed_time(const struct s_gameclock *clock)
{
  return (clock->header->total_elapsed_time);
}
