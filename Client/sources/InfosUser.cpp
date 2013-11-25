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
  authenticate.addressIp = "127.0.0.1";
  authenticate.portTCP = 44201;
  authenticate.portUDP = 44202;
}

void	InfosUser::initGame()
{
  game.partyName = "Party Name";
  game.partyPassword = "Party Password";
  game.nbPlayer = 0;
  game.maxPlayer = 4;
}

InfosUser::InfosUser()
{
  initAuthenticate();
  initGame();
}

InfosUser::~InfosUser()
{
}
