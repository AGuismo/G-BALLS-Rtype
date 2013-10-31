#ifndef CHECK_FILE_ABSTRACT
# define	CHECK_FILE_ABSTRACT

#include	"ACheckFileAbstract.h"
#include	<map>

#ifdef WIN32

#include	<Windows.h>


class	checkFileAbstract: public ACheckFileAbstract
{
 private:
  std::string				_fileToCheck;
  std::map<std::string, FILETIME>	_fileList;
  std::map<std::string, UPDATE>		_update;

 private:
  checkFileAbstract(const checkFileAbstract &);
  checkFileAbstract &operator=(const checkFileAbstract &);

 public:
  virtual std::map<std::string, UPDATE>			*refreshFile(void);

 public:
  checkFileAbstract(std::string &fileToCheck);
  ~checkFileAbstract() {}
};

#elif	defined (linux)
//nothing for now
#else
error "Unsupported operating system"
#endif // WIN32
#endif // !CHECK_FILE_ABSTRACT
