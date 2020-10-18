// This is where our game starts from

#include <SFML/Graphics.hpp>

using namespace sf;
int main() {
	//Crea el objeto videomode.
	VideoMode vm(1920, 1080);

	//Crea y abre una ventana para el juego.
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//Crea una textura para sostener un grafico en la GPU.
	Texture textureBackground;

	//Le carga un grafico a la textura.
	textureBackground.loadFromFile("graphics/background.png");

	//Crea un sprite el cual va a ser el fondo.
	Sprite spriteBackground;

	//Le asocia la textura al sprite.
	spriteBackground.setTexture(textureBackground);

	//Le pide al background que ocupe toda la pantalla.
	spriteBackground.setPosition(0, 0);

	//Input del jugador.
	while (window.isOpen()) {
		

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		/*
		****************************************
		Actualizar escena de juego
		****************************************
		*/

	

		/*
		****************************************
		Dibujar la escena de juego
		****************************************
		*/
		
		// Limpia todo desde el ultimo frame
		window.clear();
		// Dibuja la escena
		window.draw(spriteBackground);
		// Muestra lo que dibujamos
		window.display();
		

		
	}

	return 0;
}