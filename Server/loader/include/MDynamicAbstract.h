#ifndef MDYNAMICABSTRACT
# define	MDYNAMICABSTRACT

#include		<iostream>

class			MDynamicAbstract
{
public:
  virtual ~MDynamicAbstract() {};
  virtual bool DynamicOpen(const std::string &path) = 0;
  virtual void *DynamicLoadSym(const std::string &symName) = 0;
  virtual bool DynamicClose(void) = 0;
};

#endif // !MDYNAMICABSTRACT
