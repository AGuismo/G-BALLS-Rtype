#ifndef MENU_MANAGER_H_
# define MENU_MANAGER_H_

namespace	menu
{
  class		Manager
  {
  public:
    Manager();
    virtual ~Manager();

  public:
    void	initialize();
    void	update();

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);
  };

}

#endif /* MENU_MANAGER_H_ */
