#ifndef DATABASE_H_
# define DATABASE_H_

# include	<string>
# include	<vector>
# include	"IDatabase.hh"
# include	"ThreadMutex.hh"
# include	"types.hh"

class Database : public IDatabase
{
public:
  Database();
  virtual ~Database();

public:
  bool		loadFile(const std::string path);
  bool		saveFile(const std::string path);

public:
  bool		newClient(const std::string &login,
			  const requestCode::PasswordType &password);
  bool		delClient(const std::string &login,
			  const requestCode::PasswordType &password);
  bool		modClientPass(const std::string &login,
			      const requestCode::PasswordType &oldpassword,
			      const requestCode::PasswordType &newpassword);
  bool		modClientSessionID(const std::string &login,
				   const requestCode::SessionID sessionID);

private:
  Database(Database const&);
  Database& operator=(Database const&);

public:
  save::Backup &	save(save::Backup &);
  save::Backup &	load(save::Backup &);

private:
  struct			Client
  {
    std::string			login;
    requestCode::PasswordType	password;
    requestCode::SessionID	session;
  };

  struct			Predicate : std::unary_function<Client, bool>
  {
    Predicate(const std::string &login): _login(login) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login);
    }
    const std::string	_login;
  };

private:
  typedef std::vector<Client>	client_list;

private:
  client_list			_clients;
  Thread::Mutex			_lock;
};

#endif /* DATABASE_H_ */
