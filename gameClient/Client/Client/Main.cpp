#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include	<iostream>
#include	"gameWindow.h"

int main()
{
	gameWindow					gameW(std::string("I dont care"), 1280, 720);

	if (!gameW.load())
	{
		std::cerr << "Error loading game" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}
	gameW.run();
	return 0;
}