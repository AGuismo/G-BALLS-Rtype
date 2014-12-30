#include	<fstream>
#include	"Database.hh"
#include	"Backup.hpp"
#include	"Env.hh"

Database	&Database::getInstance()
{
  static Database	db;

  return (db);
}

Database::Database()
{

}

Database::~Database()
{

}

bool			Database::loadFile(const std::string path)
{
  std::fstream		stream;
  save::Backup		bak;

  stream.open(path.c_str(), std::ios_base::in);
  if (!stream.is_open())
    return (false);
  try
    {
      stream >> bak;
    }
  catch (save::invalid_argument &e)
    {
      std::cerr << "Database: Unable to load file " << path << std::endl
		<< "Error detail: " << e.what() << std::endl;
      return (false);
    }
  load(bak);
  return (true);
}

bool		Database::saveFile(const std::string path)
{
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
  Ruint16		clientSize = _clients.size();

  backup << clientSize;
  for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
      Ruint16	len = it->login.size();
      backup << len;
      backup.push(it->login, len);
      backup.push(it->password, rtype::Env::PASS_SIZE);
      backup << it->rights;
    }
  return (backup);
}

save::Backup &	Database::load(save::Backup &backup)
{
  Thread::MutexGuard	guard(_lock);
  Ruint16		nbClients;

  backup >> nbClients;
  for (client_list::size_type it = 0; it < nbClients; ++it)
    {
      Client	c;
      Ruint16	len;

      backup >> len;
      backup.pop(c.login, len);
      backup.pop(c.password, rtype::Env::PASS_SIZE);
      backup >> c.rights;
      _clients.push_back(c);
    }
  return (backup);
}

bool		Database::newClient(const std::string &login,
				    const requestCode::PasswordType &password,
				    const database::Rights right_level,
				    bool trunc)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login));
  Client		newC;

  if (it != _clients.end() && !trunc)
    return (false);
  newC.login = login;
  newC.password = password;
  newC.session = 0;
  newC.rights = right_level;
  if (trunc && it != _clients.end())
    {
      *it = newC;
      return (true);
    }
  _clients.push_back(newC);
  return (true);
}

bool		Database::delClient(const std::string &login,
				    const requestCode::PasswordType &password)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login));

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
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login));

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
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login));

  if (it == _clients.end())
    return (false);
  it->session = sessionID;
  return (true);
}

bool		Database::getClient(const std::string &login, Client &client)
{
  Thread::MutexGuard	guard(_lock);
  client_list::iterator it = std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login));

  if (it == _clients.end())
    return (false);
  client = *it;
  return (true);
}


bool		Database::clientExist(const std::string &login)
{
  return (std::find_if(_clients.begin(), _clients.end(), PredicateLogin(login)) != _clients.end());
}

bool		Database::clientExist(const std::string &login,
				      const requestCode::PasswordType &password)
{
  return (std::find_if(_clients.begin(), _clients.end(),
		       PredicateLoginPass(login, password)) != _clients.end());
}

bool		Database::clientExist(const std::string &login,
				      const requestCode::PasswordType &password,
				      const database::Rights rights)
{
  return (std::find_if(_clients.begin(), _clients.end(),
		       PredicateLoginPassRights(login, password, rights)) != _clients.end());
}
