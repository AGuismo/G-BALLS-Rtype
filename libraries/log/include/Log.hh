#ifndef LOG_H_
# define LOG_H_

#include	<iostream>
#include	<sstream>
#include	<vector>

namespace	loglib
{

  class Log
  {
    typedef std::ostream& (*ostream_manipulator)(std::ostream&);

  public:
    Log(std::ostream &stream = std::cout);
    virtual ~Log();

  public:
    Log(Log const&);

  public:
    template <typename T>
    Log	&operator<<(const T &val);

    Log	&operator<<(ostream_manipulator val);

  public:
    void	changeStream(std::ostream &stream);

  public:
    static const std::string	hexDump(const char *binary, size_t size);
    static const std::string	hexDump(const std::vector<char> &binary);
    static const std::string	hexDump(const std::vector<unsigned char> &binary);

  private:
    void	flush();

  private:
    Log& operator=(Log const&);

  private:
    std::ostream	*_stream;
    std::stringstream	_buffer;
  };
}

# include	"Log.tpp"

#endif /* LOG_H_ */
