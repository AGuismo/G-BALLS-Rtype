#ifndef DATABASE_H_
# define DATABASE_H_

# include	<string>
# include	<vector>
# include	"IDatabase.hh"
# include	"ThreadMutex.hh"
# include	"types.hh"

namespace database
{
  static const Rights	NORMAL_USER = 0;
  static const Rights	SUPER_USER = 1;
}

class Database : public IDatabase
{
private:
  Database();
  virtual ~Database();

public:
  static Database	&getInstance();

public:
  bool		loadFile(const std::string path);
  bool		saveFile(const std::string path);

public:
  bool		newClient(const std::string &login,
			  const requestCode::PasswordType &password,
			  const database::Rights right_level = database::NORMAL_USER,
			  bool trunc = false);
  bool		delClient(const std::string &login,
			  const requestCode::PasswordType &password);
  bool		modClientPass(const std::string &login,
			      const requestCode::PasswordType &oldpassword,
			      const requestCode::PasswordType &newpassword);
  bool		modClientSessionID(const std::string &login,
				   const requestCode::SessionID sessionID);
  bool		clientExist(const std::string &login);
  bool		clientExist(const std::string &login,
			    const requestCode::PasswordType &password);
  bool		clientExist(const std::string &login,
			    const requestCode::PasswordType &password,
			    const database::Rights rights);
private:
  Database(Database const&);
  Database& operator=(Database const&);

public:
  save::Backup &	save(save::Backup &);
  save::Backup &	load(save::Backup &);

public:
  struct			Client
  {
    std::string			login;
    requestCode::PasswordType	password;
    requestCode::SessionID	session;
    database::Rights		rights;

    Client() : session(0), rights(0) {}
  };

public:
  bool		getClient(const std::string &login, Client &);

private:
  struct			PredicateLogin : public std::unary_function<Client, bool>
  {
    PredicateLogin(const std::string &login): _login(login) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login);
    }
  protected:
    const std::string	_login;
  };

  struct			PredicateLoginPass : public PredicateLogin
  {
    PredicateLoginPass(const std::string &login,
		       requestCode::PasswordType p): PredicateLogin(login), _pass(p) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login && _pass == obj.password);
    }
  protected:
    const requestCode::PasswordType	_pass;
  };

  struct			PredicateLoginPassRights : public PredicateLoginPass
  {
    PredicateLoginPassRights(const std::string &login,
			     requestCode::PasswordType p,
			     database::Rights r): PredicateLoginPass(login, p), _right(r) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login && _pass == obj.password && _right == obj.rights);
    }
  protected:
    const database::Rights	_right;
  };

private:
  typedef std::vector<Client>	client_list;

private:
  client_list			_clients;
  Thread::Mutex			_lock;
};

#endif /* DATABASE_H_ */
