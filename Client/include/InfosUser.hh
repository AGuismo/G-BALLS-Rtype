#ifndef INFOS_USER_H_
# define INFOS_USER_H_

# include	<iostream>

class InfosUser
{
public:
  struct
  {
    std::string			login;
    std::string			password;
    std::string			addressIp;
    std::string			port;
  }				authenticate;

public:
  struct
  {
    std::string			partyName;
    std::string			partyPassword;
  }				create;

public:
  static InfosUser	&getInstance();

private:
  void	initAuthenticate();
  void	initCreate();

private:
  InfosUser();
  virtual ~InfosUser();
  InfosUser	&operator=(const InfosUser &);
  InfosUser(const InfosUser &);
};

#endif /* INFOS_USER_H_ */
