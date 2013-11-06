#include	"RequestQueue.hh"

RequestQueue::RequestQueue()
{

}

RequestQueue::~RequestQueue()
{

}

ARequest		*RequestQueue::requestPop(void)
{
  Thread::MutexGuard	g(_locker);

  if (_queue.size() == 0)
    return (0);

  ARequest		*req = _queue.front();
  _queue.pop();
  return (req);
}

void			RequestQueue::requestPush(ARequest *req)
{
  Thread::MutexGuard	g(_locker);

  _queue.push(req);
}

bool			RequestQueue::empty()
{
  Thread::MutexGuard	g(_locker);

  return (_queue.empty());
}
