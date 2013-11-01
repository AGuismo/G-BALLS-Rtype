#ifndef ENV_H_
# define ENV_H_

namespace rtype
{
  class Env
  {
  public:
    static const unsigned short int	TCP_SERVER_PORT = 44201;
    static const unsigned short int	UDP_SERVER_PORT = 44202;

  public:
    static Env	&getInstance();

  private:
    Env();
    virtual ~Env();
    Env	&operator=(const Env &);
    Env(const Env &);
  };
}

#endif /* ENV_H_ */
