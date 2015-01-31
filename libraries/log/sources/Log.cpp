#include	<sstream>
#include	<iomanip>
#include	"Log.hh"

using namespace loglib;

Log::Log(std::ostream &stream):
  _stream(&stream)
{
}

Log::~Log()
{
}

Log::Log(const Log &src):
  _stream(src._stream)
{
}

void	Log::changeStream(std::ostream &stream)
{
	Thread::MutexGuard	guard(_bufferLock);
	_stream = &stream;
}

Log	&Log::operator<<(Log::ostream_manipulator manipulator)
{
	Thread::MutexGuard	guard(_bufferLock);
  std::string	str;

  _buffer << manipulator;
  if (*_buffer.str().rbegin() == '\n')
    flush();
  return (*this);
}

void	Log::flush()
{
  time_t	rawtime;
  struct tm	*timeinfo;
  char	date[80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (date, 80, "%x %X %Z", timeinfo);

  *_stream << "[" << date << "]: " << _buffer.str() << std::flush;
  _buffer.str("");
}

const std::string	Log::hexDump(const char *binary, size_t size)
{
  return (hexDump(std::vector<unsigned char>((unsigned char *)binary, (unsigned char *)(binary + size))));
}

const std::string	Log::hexDump(const std::vector<char> &binary)
{
  return (hexDump(std::vector<unsigned char>(binary.begin(), binary.end())));
}

const std::string	Log::hexDump(const std::vector<unsigned char> &binary)
{
  std::ostringstream	ss;
  unsigned long		address = 0;
  unsigned char		buf[16];
  size_t		nread;

  ss << std::endl << std::setw(21) << " " << "Log: HexDump" << std::endl;
  for (std::vector<unsigned char>::const_iterator it = binary.begin(); it != binary.end();)
  {
    // Show the address
    ss << std::hex << std::setfill('0') << std::setw(8) << address << ' '; // 9

    for (nread = 0;it != binary.end() && nread < 16; ++nread, ++it)
      buf[nread] = *it;

    // Show the hex codes
    for (size_t i = 0; i < 16; i++) // 36
    {
      if (i % 4 == 0)
	ss << ' ';
      if (i < nread)
	ss << std::hex << std::setfill('0') << std::setw(2) << (unsigned)buf[i];
      else
	ss << "  ";
    }

    ss << "  "; // 2
    for (size_t i = 0; i < nread; ++i) // 8
    {
      if (!isprint(buf[i]))
	ss << '.';
      else
	ss << buf[i];
    }

    ss << std::endl;
    address += 16;
  }
  return (ss.str());
}

