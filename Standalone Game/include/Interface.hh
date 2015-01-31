#ifndef INTERFACE_H_
# define INTERFACE_H_

# include	<map>
# include	<string>

class AWidget;

class Interface
{
  typedef std::map<std::string, AWidget *>	interface_type;
private:
  Interface(void);
  virtual ~Interface(void);

public:
  static Interface	&getInstance(void);

public:
  void			addWidget(const std::string &, AWidget *);
  void			delWidget(const std::string &);
  AWidget		*getWidget(const std::string &);

private:
  Interface(Interface const&);
  Interface& operator=(Interface const&);

private:
  interface_type	_lnk;
};

#endif /* INTERFACE_H_ */
