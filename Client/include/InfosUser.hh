#ifndef INFOS_USER_H_
# define INFOS_USER_H_

# include	<iostream>
# include	"RequestCode.hh"

class InfosUser
{
public:
  struct
  {
    std::string			login;
    std::string			password;
    std::string			addressIp;
    unsigned short int		portTCP;
    unsigned short int		portUDP;
    requestCode::SessionID	id;
  }				authenticate;

public:
  struct
  {
    std::string			partyName;
    std::string			partyPassword;
    unsigned int		nbPlayer;
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
