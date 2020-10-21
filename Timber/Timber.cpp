
#include <SFML/Graphics.hpp>

using namespace sf;
/// <summary>
/// Mains this instance.
/// </summary>
/// <returns></returns>
int main() {
	//Crea el objeto videomode.
	VideoMode vm(1600, 900);

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

	//--------Hace un sprite de un arbol--------
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(650, 0);

	//--------Hace el sprite de la abeja--------
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 200);

	//Movimiento de la abeja.
	bool beeActive = false;

	//Velocidad de la abeja.
	float beeSpeed = 0.0f;

	//--------Hace el sprite de las nubes--------
	Texture textureCloud;

	//Cargo la textura.
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//Las posiciono en diferentes alturas.
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 100);
	spriteCloud3.setPosition(0, 200);

	//Se fija si están en pantalla.
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	//Movimiento de las nubes.

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Inicializa una variable reloj (para controlar las velocidades).
	Clock clock;

	while (window.isOpen()) {
		//Input del jugador.
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		/*
		****************************************
		Actualizar escena de juego
		****************************************
		*/

		//Diferencia de tiempo entre dos actualizaciones.
		Time deltaTime = clock.restart();

		//Configurar la abeja.
		if (!beeActive) {
			//Velocidad de la abeja.
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			//Altura de la abeja.
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);

			beeActive = true;
		}
		else
			//Mover la abeja.
		{
			spriteBee.setPosition(
				spriteBee.getPosition().x - (beeSpeed * deltaTime.asSeconds()),
				spriteBee.getPosition().y);

			//Verificar si llego al borde de la pantalla.
			if (spriteBee.getPosition().x < -100)
			{
				//La desactivo para que dibuje un nuevo frame.
				beeActive = false;
			}
		}

		//Configuracion de las nubes.
		//nube1
		if (!cloud1Active)
		{
			//Velocidad de la nube.
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			//Altura de la nube.
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}
		else {
			spriteCloud1.setPosition(
				spriteCloud1.getPosition().x + (cloud1Speed * deltaTime.asSeconds()),
				spriteCloud1.getPosition().y);
			// Verifica que la nube llegue al lado derecho
			if (spriteCloud1.getPosition().x > 1920)
			{
				cloud1Active = false;
			}
		}

		if (!cloud2Active)
		{
			//Velocidad de la nube.
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);

			//Altura de la nube.
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		}
		else {
			spriteCloud2.setPosition(
				spriteCloud2.getPosition().x + (cloud2Speed * deltaTime.asSeconds()),
				spriteCloud2.getPosition().y);
			// Verifica que la nube llegue al lado derecho
			if (spriteCloud2.getPosition().x > 1920)
			{
				cloud2Active = false;
			}
		}

		if (!cloud3Active)
		{
			//Velocidad de la nube.
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);

			//Altura de la nube.
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		}
		else {
			spriteCloud3.setPosition(
				spriteCloud3.getPosition().x + (cloud3Speed * deltaTime.asSeconds()),
				spriteCloud3.getPosition().y);
			// Verifica que la nube llegue al lado derecho
			if (spriteCloud3.getPosition().x > 1920)
			{
				cloud3Active = false;
			}
		}

		/*
		****************************************
		Dibujar la escena de juego
		****************************************
		*/

		// Limpia todo desde el ultimo frame.
		window.clear();
		// Dibuja la escena
		window.draw(spriteBackground);

		//Dibuja las nubes
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		//Dibuja el arbol
		window.draw(spriteTree);

		//Dibuja las abejas
		window.draw(spriteBee);

		// Muestra lo que dibujamos
		window.display();
	}

	return 0;
}