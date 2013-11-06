#ifndef REQUESTQUEUE_H_
# define REQUESTQUEUE_H_

# include	<queue>
# include	"ThreadMutex.hh"

class ARequest;

class RequestQueue
{
public:
  typedef std::queue<ARequest *>	queue_type;
public:
  RequestQueue();
  virtual ~RequestQueue();

public:
  ARequest	*requestPop();
  void		requestPush(ARequest *);
  bool		empty();

private:
  RequestQueue(RequestQueue const&);
  RequestQueue& operator=(RequestQueue const&);

private:
  //Thread::Mutex	_locker;
  queue_type	_queue;
};

#endif /* REQUESTQUEUE_H_ */
