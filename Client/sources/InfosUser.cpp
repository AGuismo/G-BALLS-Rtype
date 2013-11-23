#include	"InfosUser.hh"

InfosUser		&InfosUser::getInstance()
{
  static InfosUser	singleton;

  return (singleton);
}

void	InfosUser::initAuthenticate()
{
  authenticate.login = "Login";
  authenticate.password = "Password";
  authenticate.addressIp = "Address Ip";
  authenticate.portTCP = 0;
  authenticate.portUDP = 0;
}

void	InfosUser::initCreate()
{
  create.partyName = "Party Name";
  create.partyPassword = "Party Password";
}

InfosUser::InfosUser()
{
  initAuthenticate();
  initCreate();
}

InfosUser::~InfosUser()
{
}
