#include	"Application.hh"

int		main(int argc, const char *argv[])
{
  Application	*app;

  try
    {
      app = new Application;
    }
  catch (const Application::InitExcept &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  app->run();
  (void)argc;
  (void)argv;
  delete app;
  return (0);
}
