#ifndef GAMEMANAGER_H_
# define GAMEMANAGER_H_

namespace	game
{
  class Manager
  {
  public:
    Manager();
    ~Manager();

  public:
    void	initialize();
    void	update();

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);
  };
}

#endif /* GAMEMANAGER_H_ */
