//
// main.cpp for main in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 12:59:21 2013 brigno
// Last update Thu Oct 24 09:59:31 2013 brigno
//

#include	"Window.hh"

int	main()
{
  Window myWin("R-type", 1600, 900);
  Background	myBackground("Images/background.png", "Images/background2.png");
  Title		myTitle("Images/title.png");
  Form		myForm("Images/form.png");

  myWin.launchWindow();
}
