#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Posición del jugador o de la rama.
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


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

	//--------Hace un sprite de un arbol--------
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(820, 0);

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

	//Barra de tiempo
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Variable que indica si el juego está pausado.
	bool paused = true;

	//Puntaje en pantalla.
	int score = 0;

	//Campos de texto.
	Text messageText;
	Text scoreText;

	//Fuente para el texto.
	Font font;
	font.loadFromFile("fonts/KOMIKAP.ttf");

	//Asignamos la fuente al mensaje.
	messageText.setFont(font);
	scoreText.setFont(font);

	//Asigno el mensaje de la fuente.
	messageText.setString("Presionar enter para comenzar");
	scoreText.setString("Puntaje = 0");

	//Aumentar el tamaño del texto.
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Selecciona colores de texto.
	messageText.setFillColor(Color::White);
	messageText.setOutlineColor(Color::White);
	scoreText.setFillColor(Color::White);
	scoreText.setOutlineColor(Color::White);

	//Posición del texto.
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	//Preparar 6 ramas
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	//Asignar la textura para cada branch sprite.
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		//Tengo que asignarle el origen al centro así luego las puedo espejar
		//sin tener que cambiarle la posición.
		branches[i].setOrigin(220, 20);
	}

	


	while (window.isOpen()) {
		//Input del jugador.
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;

			//Resetear tiempo y puntaje.
			score = 0;
			timeRemaining = 6;
		
		}
			

		/*
		****************************************
		Actualizar escena de juego
		****************************************
		*/
		if (!paused) {

		
			//Diferencia de tiempo entre dos actualizaciones.
			Time deltaTime = clock.restart();
			
			//Restar el tiempo restante.
			timeRemaining -= deltaTime.asSeconds();

			//Acomodar la barra de tiempo.
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				//pausar el juego.
				paused = true;

				//Cambiar el texto que se muestra al jugador.
				messageText.setString("Se acabó el tiempo!");

				//Reposicionar el texto con el tamaño nuevo.
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1090 / 2.0f, 1080 / 2.0f);
			
			}

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

			//Actualiza el puntaje mientras el juego no esté en pausa.
			std::stringstream ss;
			ss << "Puntaje = " << score;
			scoreText.setString(ss.str());

			//Actualizar los sprites de las ramas.
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;

				if (branchPositions[i] == side::LEFT) {
					//Si está del lado izquierdo voy a posicionar el sprite a la izquierda.
					branches[i].setPosition(610, height);

					//Si está del lado izquierdo voy a rotar el sprite a la izquierda.
					branches[i].setRotation(180);
				}

				else if (branchPositions[i] == side::RIGHT) {

					//Si está del lado derecho lo roto.
					branches[i].setPosition(1330, height);

					//Rotacion del sprite normal
					branches[i].setRotation(0);

				}
				else
				{
					//Ocultamos la rama
					branches[i].setPosition(3000, height);
				}
			}



		} //end if (!paused)


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

		//Dibujar las ramas
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);

		}

		//Dibuja el arbol
		window.draw(spriteTree);

		//Dibuja las abejas
		window.draw(spriteBee);

		//Dibuja el puntaje
		window.draw(scoreText);

		//Dibujar la barra de tiempo.
		window.draw(timeBar);

		//Dibuja el mensaje para comenzar.
		if (paused)
			window.draw(messageText);

		// Muestra lo que dibujamos.
		window.display();
	}

	return 0;
}

//Mueve las ramas un lugar abajo.
void updateBranches(int seed) {

	for (int j = NUM_BRANCHES-1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	//Aparecer una nueva rama en la posición 0.
	//LEFT, RIGHT o NONE.
	srand((int)time(0) + seed);
	int random = (rand() % 5);
	switch (random) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;

	}


}