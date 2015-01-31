namespace	loglib
{

  template <typename T>
  Log		&Log::operator<<(const T &val)
  {
	Thread::MutexGuard	guard(_bufferLock);

    _buffer << val;
    return (*this);
  }

}
