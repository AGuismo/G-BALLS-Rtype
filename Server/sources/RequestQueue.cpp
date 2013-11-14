#include	"RequestQueue.hh"

RequestQueue::RequestQueue()
{

}

RequestQueue::~RequestQueue()
{

}

ARequest		*RequestQueue::requestPop(void)
{
  if (_queue.size() == 0)
    return (0);

  ARequest		*req = _queue.front();
  _queue.pop();
  return (req);
}

void			RequestQueue::requestPush(ARequest *req)
{
  _queue.push(req);
}

bool			RequestQueue::empty()
{
  return (_queue.empty());
}
