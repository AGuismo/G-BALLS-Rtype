#ifndef DATABASE_H_
# define DATABASE_H_

# include	<string>
# include	<vector>
# include	"IDatabase.hh"
# include	"ThreadMutex.hh"
# include	"ProtocolTypes.hh"

namespace database
{
  static const rtype::protocol::database::Rights	NORMAL_USER = 0;
  static const rtype::protocol::database::Rights	SUPER_USER = 1;
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
			  const rtype::protocol::PasswordType &password,
			  const rtype::protocol::database::Rights right_level = database::NORMAL_USER,
			  bool trunc = false);
  bool		delClient(const std::string &login,
			  const rtype::protocol::PasswordType &password);
  bool		modClientPass(const std::string &login,
			      const rtype::protocol::PasswordType &oldpassword,
			      const rtype::protocol::PasswordType &newpassword);
  bool		modClientSessionID(const std::string &login,
				   const rtype::protocol::SessionID sessionID);
  bool		clientExist(const std::string &login);
  bool		clientExist(const std::string &login,
			    const rtype::protocol::PasswordType &password);
  bool		clientExist(const std::string &login,
			    const rtype::protocol::PasswordType &password,
			    const rtype::protocol::database::Rights rights);
private:
  Database(Database const&);
  Database& operator=(Database const&);

public:
  save::Backup &	save(save::Backup &);
  save::Backup &	load(save::Backup &);

public:
  struct			Client
  {
    std::string				login;
    rtype::protocol::PasswordType	password;
    rtype::protocol::SessionID		session;
    rtype::protocol::database::Rights	rights;

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
		       rtype::protocol::PasswordType p): PredicateLogin(login), _pass(p) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login && _pass == obj.password);
    }
  protected:
    const rtype::protocol::PasswordType	_pass;
  };

  struct			PredicateLoginPassRights : public PredicateLoginPass
  {
    PredicateLoginPassRights(const std::string &login,
			     rtype::protocol::PasswordType p,
			     rtype::protocol::database::Rights r): PredicateLoginPass(login, p), _right(r) {}
    bool	operator()(const Client obj) const
    {
      return (_login == obj.login && _pass == obj.password && _right == obj.rights);
    }
  protected:
    const rtype::protocol::database::Rights	_right;
  };

private:
  typedef std::vector<Client>	client_list;

private:
  client_list			_clients;
  Thread::Mutex			_lock;
};

#endif /* DATABASE_H_ */
