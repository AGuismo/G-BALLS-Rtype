#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include	<iostream>
#include	<SFML/Graphics.hpp>

int main()
{
/*	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Texture		vTexture;
	sf::Sprite		vImg;

	if (!vTexture.loadFromFile("./Images/r-typesheet42.png", sf::IntRect(80,0,80,80)))
		std::cerr << "Loading Error" << std::endl;

	vImg.setTexture(vTexture);
	vImg.setPosition(200, 200);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(vImg);
		window.display();
	}
	*/
	return 0;
}