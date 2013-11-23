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
  authenticate.port = "Port";
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
