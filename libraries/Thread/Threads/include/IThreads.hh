#ifndef ITHREADS_H_
# define ITHREADS_H_

template <typename T>
class IThreads
{
public:
  virtual ~IThreads() {}

public:
  virtual bool	run() = 0;
  virtual bool	cancel() = 0;
  virtual bool	join() = 0;
  virtual bool	isActivated() const = 0;
};

#endif /* ITHREADS_H_ */
