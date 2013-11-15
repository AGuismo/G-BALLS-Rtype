#include	<fstream>
#include	"Database.hh"
#include	"Backup.hpp"

Database::Database()
{

}

Database::~Database()
{

}

bool		Database::loadFile(const std::string path)
{
  Thread::MutexGuard	guard(_lock);
  std::ifstream	stream(path.c_str());
  save::Backup	bak;

  if (stream.bad())
    return (false);
  stream >> bak;
  load(bak);
  return (true);
}

bool		Database::saveFile(const std::string path)
{
  Thread::MutexGuard	guard(_lock);
  std::ofstream	stream(path.c_str());
  save::Backup	bak;

  if (stream.bad())
    return (false);
  save(bak);
  stream << bak;
  return (true);
}

save::Backup &	Database::save(save::Backup &backup)
{
  Thread::MutexGuard	guard(_lock);
  backup << _clients.size();
  for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
    backup << it->login << it->password;
  return (backup);
}

save::Backup &	Database::load(save::Backup &backup)
{
  Thread::MutexGuard	guard(_lock);
  client_list::size_type	nbClients;
  backup >> nbClients;
  for (client_list::size_type it = 0; it < nbClients; ++it)
    {
      Client	c;

      backup >> c.login >> c.password;
      _clients.push_back(c);
    }
  return (backup);
}

bool		Database::newClient(const std::string &login,
				    const requestCode::PasswordType &password)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), Predicate(login));
  Client		newC;

  if (it == _clients.end())
    return (false);
  newC.login = login;
  newC.password = password;
  newC.session = 0;
  _clients.push_back(newC);
  return (true);
}

bool		Database::delClient(const std::string &login,
				    const requestCode::PasswordType &password)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), Predicate(login));

  if (it == _clients.end())
    return (false);
  if (it->password != password)
    return (false);
  _clients.erase(it);
  return (true);
}

bool		Database::modClientPass(const std::string &login,
					const requestCode::PasswordType &oldpassword,
					const requestCode::PasswordType &newpassword)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), Predicate(login));

  if (it == _clients.end())
    return (false);
  if (it->password != oldpassword)
    return (false);
  it->password = newpassword;
  return (true);
}

bool		Database::modClientSessionID(const std::string &login,
					     const requestCode::SessionID sessionID)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), Predicate(login));

  if (it == _clients.end())
    return (false);
  it->session = sessionID;
  return (true);
}
